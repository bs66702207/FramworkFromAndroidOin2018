#ifndef __CHJ_CAR_DIAG_READER_H__
#define __CHJ_CAR_DIAG_READER_H__

//#include <utils/RefBase.h>
#include <utils/Looper.h>
#include <utils/Timers.h>
#include <mutex>

#include <signal.h>
#include "CHJDiagCommBase.h"


namespace android
{

typedef struct
{
    nsecs_t when;
    String8 message;
}RawMsgStr;

typedef std::vector<RawMsgStr> SENDMSGQUEUE;

/***********CHJCarDiagReaderInterface*************************/
  class CHJCarDiagReaderInterface : public virtual RefBase
 {
    protected:
       CHJCarDiagReaderInterface(){}
       virtual ~CHJCarDiagReaderInterface(){}

    public:
        virtual void getUDSMessage( String8 mMessage )=0;
 };


/*************CHJCarDiagReader*********************************/
 class CHJCarDiagReader : public virtual RefBase
 {
    public:
        
        CHJCarDiagReader( const sp<CHJCarDiagReaderInterface>&mPtrDiagService     );

        
        ~CHJCarDiagReader();

        void loopReader();
        void queueSendingMsg(  String8 msg);

   private:
        void recvSendUDSMsg();
        void sendMsgsLocked(  );
        
   private:
        // The event queue.
        SENDMSGQUEUE mSendMsgQueue;
        
        String8 mCurSendMsg;
        std::mutex mSendMsgMutex;
        sp<Looper> mLooper;
        nsecs_t mSocketLoopDueTime;
        std::atomic<bool> mExit { false };
        sp<CHJDiagCommBase> mCommPtr;
        sp<CHJCarDiagReaderInterface> mCHJCarDiagService;
        
    
 };

}
#endif /*__CHJ_CAR_DIAG_READER_H__*/
