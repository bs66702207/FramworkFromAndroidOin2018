#include "CHJCarDiagReader.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <vector>
#include <netinet/in.h>


namespace android
{

#define FREE_POINT(p) do{free(p);p=NULL;}while(0)

const nsecs_t SOCKET_LOOP_TIMEOUT = 500;

static inline nsecs_t time_now() 
{
    return systemTime(SYSTEM_TIME_MONOTONIC);
}


/*---------CHJDiagSocketComm------------*/
//  const  sockaddr_un CHJDIAG_SERVER_PATH = {AF_UNIX, "\0chjdiagservice"};

#define CHJ_SOCKET_NAME "\0chjdiagservice"
#define CHJ_SOCKET_NAME_LEN (sizeof(CHJ_SOCKET_NAME)-1)
#define CHJ_SOCKET_DATA_PACK_LEN  1*1024



  class CHJDiagSocketComm : public CHJDiagCommBase
  {
   public:
      CHJDiagSocketComm();
     ~CHJDiagSocketComm();
 
     int open();
     int connect();
     int write( String8 msg );
     String8 read();
 
     void stop();
     int getSocketFd();  
 
    private:
        int mSocketFd;
        int mCurSockFd;
        std::atomic<int> mExit;
        std::mutex mMutex;

       typedef struct MessageStr
       {
           uint32_t msgLen;
           char pBuf[0];
       }mSendMessageStr;
       //mSendMessageStr mWriteBufStr;

#if 0
       static void sigpipeHandler(int sig);
#endif   
  };


/*-------CHJCarDiagReader------------*/
  CHJCarDiagReader::CHJCarDiagReader( const sp<CHJCarDiagReaderInterface>&mPtrDiagService      ):
    mSocketLoopDueTime( LONG_LONG_MAX ),
    mCHJCarDiagService( mPtrDiagService )
  {
      mLooper = new Looper( false );
      mCommPtr = new CHJDiagSocketComm();

      mCurSendMsg.clear();
  }
     
  CHJCarDiagReader::~CHJCarDiagReader()
  {
  }


  
  void CHJCarDiagReader::queueSendingMsg(   String8 msg )
  {
     {//lock
      /*1. init one struct, store data*/
      RawMsgStr mRawMsgStr;
      mRawMsgStr.when = 0;/*systemTime( SYSTEM_TIME_MONOTONIC );*/
      mRawMsgStr.message = msg;

      /*2. put message struct into queue*/
      std::lock_guard<std::mutex> lock( mSendMsgMutex );
      mSendMsgQueue.push_back( mRawMsgStr );
      //DIAG_D("msendMsgQueue lenght=%d",mSendMsgQueue.size());
      
     }//unlock

      /*3. wake communication thread*/
      mLooper->wake();

      
  }

  void CHJCarDiagReader::sendMsgsLocked()
  {
      std::lock_guard<std::mutex> lock( mSendMsgMutex );
      
      if( mSendMsgQueue.empty() )
      {
          return;
      }

      int count = mSendMsgQueue.size();
      for( int i=0; i<count; i++ )
      {
          int ret = mCommPtr->write( mSendMsgQueue[i].message );
          if ( ret<0 )
          {
              DIAG_D("%s: send message failed",__FUNCTION__);
          }

          mSendMsgQueue[i].message.clear();
      }

      mSendMsgQueue.clear();
      //DIAG_D("%s: send message sucess and mSendMsgQueue size=%d",__FUNCTION__,mSendMsgQueue.size());
  }


  void CHJCarDiagReader::recvSendUDSMsg()
  {
      String8 msg = mCommPtr->read();
      if ( msg.size() > 0 )
      {
          /*we found message from UDS server, so send it to java*/
          //DIAG_D("%s __msg.size=%d _ \n",__func__,msg.size());
          mCHJCarDiagService->getUDSMessage( msg );
      }

      /*need send message to UDS*/
      sendMsgsLocked();
  }
  
  void CHJCarDiagReader::loopReader()
  {
      
      if ( mExit )
      {
          return;
      }

      int mSocketRetval = mCommPtr->open();
      if ( mSocketRetval<0 )
      {
          mExit = true;
      }

      while( !mExit )
      {
          
          //nsecs_t currentTime = time_now();
          //DIAG_E("__loopReader current time=%ld__\n", currentTime/1000);

          if ( mCommPtr->getSocketFd() == -1 )
          {
              mSocketRetval = mCommPtr->connect();
          }
          
          if ( mSocketRetval>= 0 )
          {
              /*here should read data from socket and check send data*/
              recvSendUDSMsg();
          }
          
          mLooper->pollOnce( SOCKET_LOOP_TIMEOUT );
      }
  }




 CHJDiagSocketComm::CHJDiagSocketComm()
 {
     mSocketFd = -1;
     mCurSockFd = -1;
     mExit = 0;
 }

 CHJDiagSocketComm::~CHJDiagSocketComm()
 {
 }

 int CHJDiagSocketComm::open()
 {
     int retVal = -1;
     sockaddr_un addr;
     socklen_t addrlen;
     int maxpath = sizeof(addr.sun_path);
     int pathlen = CHJ_SOCKET_NAME_LEN;

     memset(&addr, 0, sizeof(addr));
     addr.sun_family = AF_UNIX;
     memcpy(addr.sun_path, CHJ_SOCKET_NAME, CHJ_SOCKET_NAME_LEN);
 
     mSocketFd = socket(AF_UNIX, SOCK_STREAM, 0);
     if ( mSocketFd < 0 )
     {
         DIAG_E("%s: socket() failed, mSocketFd=%d, errno=%d", __func__, mSocketFd, errno);
         mSocketFd = -1;
         return -errno;
     }

     addrlen = pathlen + sizeof(addr.sun_family);

     unlink( CHJ_SOCKET_NAME );
     
     retVal = bind( mSocketFd, reinterpret_cast<const sockaddr*>(&addr), addrlen );
     if(retVal < 0) 
     {
         DIAG_E("%s: Error on binding: retVal=%d, errno=%d", __func__, retVal, errno);
         close( mSocketFd );
         mSocketFd = -1;
         return -errno;
     }

     retVal = listen( mSocketFd, 1 );
     if ( retVal <0 )
     {
         DIAG_E("%s: Error on listen: retVal=%d, errno=%d", __func__, retVal, errno);
         close( mSocketFd );
         mSocketFd = -1;
         return -errno;
     }
     
     // Set the socket to be non-blocking so we can poll it continouously
     retVal = fcntl( mSocketFd, F_SETFL, O_NONBLOCK );
     if ( retVal <0 )
     {
         DIAG_E("%s: Error on fcntl NONBLOCK: retVal=%d, errno=%d", __func__, retVal, errno);
         close( mSocketFd );
         mSocketFd = -1;
         return -errno;
     }

     
     //signal( SIGPIPE|SIGHUP|SIGINT|SIGSTOP, sigpipeHandler );
     return OK;
 }

 int CHJDiagSocketComm::connect()
 {
     sockaddr_un mClientAddr;
     socklen_t mClientLen = sizeof( mClientAddr );


     int tempSocketFd = accept( mSocketFd, reinterpret_cast<struct sockaddr *>( &mClientAddr ), &mClientLen ); 
     if ( tempSocketFd >= 0 ) 
     {
         {
             std::lock_guard<std::mutex> lock(mMutex);
             mCurSockFd = tempSocketFd;
         }
     
         DIAG_D("%s: Incoming connection received on socket %d", __func__, tempSocketFd);
     } 
     else 
     {
         tempSocketFd = -1;
     }
     
     return tempSocketFd;
 }

 void CHJDiagSocketComm::stop()
 {
     if ( mExit == 0 ) 
     {
         std::lock_guard<std::mutex> lock( mMutex );
         mExit = 1;
     
         // Close  socket if it is open
         if ( mCurSockFd != -1 )
         {
             close(mCurSockFd);
             mCurSockFd = -1;
         }
     
         if ( mSocketFd != -1 ) 
         {
             close( mSocketFd );
             mSocketFd = -1;
         }
     }
 }

int CHJDiagSocketComm::write(String8 msg)
 {
     int mNumBytes = -1;
     uint32_t mMsgLength = static_cast<uint32_t>(msg.length());

     int mtempLen = sizeof(mSendMessageStr)+mMsgLength;
     mSendMessageStr *pMsgStr = ( mSendMessageStr *)malloc( mtempLen ); 
     memset( pMsgStr, 0, mtempLen);

     if( pMsgStr!= NULL )
     {
        // pMsgStr->msgLen = mMsgLength;
         DIAG_D("%s Report Message To UDS=%s",__FUNCTION__,msg.c_str());
         memcpy( pMsgStr->pBuf, msg.c_str(), mMsgLength );
         pMsgStr->msgLen = htonl( mMsgLength );
     }

    
     if( mCurSockFd )
     {
         //std::lock_guard<std::mutex> lock( mMutex );
         mNumBytes = send( mCurSockFd, pMsgStr, mtempLen, MSG_DONTWAIT );
         /*TODO: here should add connect error*/
     }

     FREE_POINT( pMsgStr );

     return mNumBytes;
 }


 String8 CHJDiagSocketComm::read()
 {
     int numBytes = 0;
     String8 dataString("");

     int JSONDataLength = 0;
     
     numBytes = recv( mCurSockFd, &JSONDataLength, sizeof(JSONDataLength), MSG_DONTWAIT );
     JSONDataLength = ntohl(JSONDataLength);
     if ( numBytes != sizeof( JSONDataLength ) )
     {
         if ( numBytes == 0 )
         {
             std::lock_guard<std::mutex> lock( mMutex );
             mCurSockFd = -1;
             DIAG_D("%s _1_socket has performed an orderly shutdown_EOF_",__FUNCTION__);
         }
         else if ( numBytes<0 )
         {
             ;//DIAG_D("%s__read1 numBytes=%d__EAGAIN=%d",__func__,numBytes,EAGAIN);
         }

         return dataString;
     }


     char *pMsg =static_cast<char *>(malloc(JSONDataLength));
     if ( !pMsg )
     {
         DIAG_D("%s __socket can not malloc buf_",__FUNCTION__);
         return dataString;
     }
     memset( pMsg, 0, JSONDataLength );
     
     // This is a variable length message.
     // Read the number of bytes to rx over the socket
     numBytes = recv( mCurSockFd, pMsg, JSONDataLength, MSG_DONTWAIT );
     if ( (numBytes == JSONDataLength) &&( JSONDataLength >0) )
     {
         // Received a message.
          dataString = String8(pMsg, JSONDataLength);
          //DIAG_D("%s__read2 numBytes=%d and msg=%s__",__func__,numBytes,dataString.c_str());
     }
     else
     {
         if ( numBytes == 0 )
         {
             std::lock_guard<std::mutex> lock( mMutex );
             mCurSockFd = -1;
             DIAG_D("%s 2__socket has performed an orderly shutdown_EOF_",__FUNCTION__);
         }
         else if ( numBytes<0 )
         {
             //DIAG_D("%s__read numBytes=%d__EAGAIN=%d",__func__,numBytes,EAGAIN);
             /*socket connected, but we can not read anything, because client does not write data*/
         }
     }


     FREE_POINT( pMsg );
     
     return dataString;
 }

 int CHJDiagSocketComm::getSocketFd()
 {
     return mCurSockFd;
 }

#if 0
 void CHJDiagSocketComm::sigpipeHandler(int sig)
 {
     signal( sig, sigpipeHandler );

     switch( sig )
     {
     case SIGPIPE:
        DIAG_D("___SIGPIPE___");
        break;
     default:
         DIAG_D("___sig=%d__",sig);
        break;
     }
 }
#endif 
}

