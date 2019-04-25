#include "CHJCarDiagDTCMonitor.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <vector>
#include <netinet/in.h>


namespace android
{
  #define DEFAULT_YEAR 2000
  const int LOOP_TIMEOUT_MSECS = 15*1000;  //15 secs

  
  CHJCarDiagDTCMonitor::CHJCarDiagDTCMonitor(const sp < CHJCarDiagReaderInterface > & mPtrDiagService, 
                                             const sp < CHJCarDiagReader > & listener):
                                             mDriverCircle(-1),
                                             mNativeDiagService( mPtrDiagService ),
                                             mListener( listener ),
                                             mNextDeviceId(1),
                                             mGroupClearAllDTC(false)
  {
      mMonitorLooper = new Looper( false );
      mDTCHal = new CHJCarDiagDTCHal();
      mVehicleInfo = new CHJCarDiagVehicleInfo();
      mDEMPowerState = DEM_CYCLE_STATE_UNKNOW;
      addDeviceLocked();
  }

  CHJCarDiagDTCMonitor::~CHJCarDiagDTCMonitor()
  {
      clearAllDeviceLocked();
  }

  /*Adding device checking function from HAL*/
  void CHJCarDiagDTCMonitor::addDeviceLocked()
  {
      /*KEY is deviceID, value is Device*/
      Device *pMainTpStatus = new Device( CHJ_DIAG_DTC_MAIN_TOUCH, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getMainTpStatus,mDTCHal ) );
      mDevices.add( pMainTpStatus->deviceId, pMainTpStatus);

      Device *pSubTPStatus = new Device( CHJ_DIAG_DTC_SUB_TOUCH, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getSecTpStatus,mDTCHal ) );
      mDevices.add( pSubTPStatus->deviceId, pSubTPStatus);
      
      Device *pMainDisplay = new Device( CHJ_DIAG_DTC_MAIN_DISPLAY, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getMainDisplayStatus,mDTCHal ) );
      mDevices.add( pMainDisplay->deviceId, pMainDisplay );

      Device *pSubDisplay = new Device( CHJ_DIAG_DTC_SUB_DISPLAY, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getSecDisplayStatus,mDTCHal ) );
      mDevices.add( pSubDisplay->deviceId, pSubDisplay );

      Device *pMainLCDGMSL = new Device( CHJ_DIAG_DTC_MAIN_LCD_GMSL, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getMainGmslStatus,mDTCHal ) );
      mDevices.add( pMainLCDGMSL->deviceId, pMainLCDGMSL );

      Device *pSubLCDGMSL = new Device( CHJ_DIAG_DTC_SUB_LCD_GMSL, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getSecGmslStatus,mDTCHal ) );
      mDevices.add( pSubLCDGMSL->deviceId, pSubLCDGMSL );

      Device *pMainTuner = new Device( CHJ_DIAG_DTC_MAIN_TUNER, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getMainTunerStatus,mDTCHal ) );
      mDevices.add( pMainTuner->deviceId, pMainTuner );

      Device *pSubTuner = new Device( CHJ_DIAG_DTC_SUB_TUNER, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getSecTunerStatus,mDTCHal ) );
      mDevices.add( pSubTuner->deviceId, pSubTuner );

      Device *pBTWifi = new Device( CHJ_DIAG_DTC_BT_WIFI, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getBTWifiStatus,mDTCHal ) );
      mDevices.add( pBTWifi->deviceId, pBTWifi );

      Device *pDSP = new Device( CHJ_DIAG_DTC_DSP, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getDspStatus,mDTCHal ) );
      mDevices.add( pDSP->deviceId, pDSP );

      Device *p4G = new Device( CHJ_DIAG_DTC_4G_COMM, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::get4GStatus,mDTCHal ) );
      mDevices.add( p4G->deviceId, p4G );

      Device *pIpod = new Device( CHJ_DIAG_DTC_MFI_COMM, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getIpodStatus,mDTCHal ) );
      mDevices.add( pIpod->deviceId, pIpod );

      Device *pLinkLoss = new Device( CHJ_DIAG_DTC_LINK_LOSS, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getEthLinkUpStatus,  mDTCHal) );
      mDevices.add( pLinkLoss->deviceId, pLinkLoss );

      Device *pInsufficientSQIValue = new Device( CHJ_DIAG_DTC_SQI_VALUE, mNextDeviceId++, std::bind(&CHJCarDiagDTCHal::getInsufficientSQIValue, mDTCHal) );
      mDevices.add( pInsufficientSQIValue->deviceId, pInsufficientSQIValue );
  }
  

  void CHJCarDiagDTCMonitor::clearDeviceLocked( Device *pDevice )
  {
      if ( pDevice != NULL )
      {
          mDevices.removeItem( pDevice->deviceId );

          FREE_POINE( pDevice );
      }
  }


  void CHJCarDiagDTCMonitor::clearAllDeviceLocked()
  {
      while (mDevices.size() > 0)
      {
          clearDeviceLocked( mDevices.valueAt( mDevices.size()-1));
      }
  }

  std::string CHJCarDiagDTCMonitor::packagePowerStateJSONData( int32_t status )
  {
      Json::Value mJsonAllMsg;
      Json::Value mJsonDataField;
      Json::FastWriter mJsonWriter;

      mJsonAllMsg[DTC_CLIENT] = Json::Value(DTC_CLIENT_DEM);
      
      mJsonDataField[DTC_DATA_FIELD_METHOD] = Json::Value(METHOD_POWER_STATE_CYCLE_FIELD);
      mJsonDataField[METHOD_POWER_STATE_CYCLE] = Json::Value(status);

      mJsonAllMsg[DTC_DATA_FIELD] = mJsonDataField;

      return mJsonWriter.write( mJsonAllMsg );
  }

  std::string CHJCarDiagDTCMonitor::packageJSONData( int32_t DTCId, int32_t status )
  {
      Json::Value mJsonAllMsg;
      Json::Value mJsonDataField;
      Json::FastWriter mJsonWriter;

      CHJCarDiagVehicleInfo::vehicleSnapShotStr mVehicleSnapShotInfoStr;

      mJsonAllMsg[DTC_CLIENT] = Json::Value(DTC_CLIENT_DEM);
      
      mJsonDataField[DTC_DATA_FIELD_METHOD] = Json::Value(DTC_DATA_FIELD_METHOD_DEM);
      mJsonDataField[DTC_DATA_FIELD_EVENTNO] = Json::Value(DTCId);
      mJsonDataField[DTC_DATA_FIELD_STATUS] = Json::Value(status);


      /*get snapshot information*/
      mVehicleInfo->getCurVehicleSnapShotInfo( &mVehicleSnapShotInfoStr );

      /*packaging snapshot information by json*/
      handleSnapShotInfo( mJsonDataField, mVehicleSnapShotInfoStr );
      

      mJsonAllMsg[DTC_DATA_FIELD] = mJsonDataField;

      return mJsonWriter.write( mJsonAllMsg );
      
  }

  void CHJCarDiagDTCMonitor::handleSnapShotInfo( Json::Value &json, CHJCarDiagVehicleInfo::vehicleSnapShotStr &snapShot )
  {
      Json::Value sysTimeJsonAry( Json::arrayValue );
      Json::Value snapShotJsonValue( Json::objectValue );


      /*system time*/
      snapShotJsonValue[DTC_DATA_ID] = CHJ_DIAG_DID_SYS_TIME;
      if( snapShot.sysTime.size() != 0 )
      {
          for (std::vector<int32_t>::const_iterator it = snapShot.sysTime.begin(); it != snapShot.sysTime.end(); ++it)
          {
             sysTimeJsonAry.append(*it);
          }

          snapShotJsonValue[DTC_SNAPSHOT_FIELD_SYSTIME] = sysTimeJsonAry;

      }
      else
      {
         snapShotJsonValue[DTC_SNAPSHOT_FIELD_SYSTIME] = DEFAULT_YEAR;
      }

      json[DTC_DATA_FIELD_SNAPSHOT].append( snapShotJsonValue );
      
      
     /*system voltage*/
      snapShotJsonValue.clear();
      snapShotJsonValue[DTC_DATA_ID] = CHJ_DIAG_DID_CUR_SYS_VOLT;
      snapShotJsonValue[DTC_SNAPSHOT_FIELD_VOLTAGE]= snapShot.sysCurVolt;
      json[DTC_DATA_FIELD_SNAPSHOT].append(snapShotJsonValue);

      /*board temperature*/
      snapShotJsonValue.clear();
      snapShotJsonValue[DTC_DATA_ID] = CHJ_DIAG_DID_BOARD_TEMP;
      snapShotJsonValue[DTC_SNAPSHOT_FIELD_BOARD_TEMP] = snapShot.boardCurTemp;
      json[DTC_DATA_FIELD_SNAPSHOT].append( snapShotJsonValue );

      /*SoC temperature*/
      snapShotJsonValue.clear();
      snapShotJsonValue[DTC_DATA_ID] = CHJ_DIAG_DID_SOC_TEMP;
      snapShotJsonValue[DTC_SNAPSHOT_FIELD_SOC_TEMP]= snapShot.socCurTemp;
      json[DTC_DATA_FIELD_SNAPSHOT].append( snapShotJsonValue );

      /*Motor speed*/
      snapShotJsonValue.clear();
      snapShotJsonValue[DTC_DATA_ID] = CHJ_DIAG_DID_MOTOR_SPEED;
      snapShotJsonValue[DTC_SNAPSHOT_FIELD_MOTOR_SPEED]= snapShot.curMotorSpeed;
      json[DTC_DATA_FIELD_SNAPSHOT].append( snapShotJsonValue );

      /*Vehicle speed*/
      snapShotJsonValue.clear();
      snapShotJsonValue[DTC_DATA_ID] = CHJ_DIAG_DID_VEHICLE_SPEED;
      snapShotJsonValue[DTC_SNAPSHOT_FIELD_VEHICLE_SPEED]= snapShot.curVehicleSpeed;
      json[DTC_DATA_FIELD_SNAPSHOT].append( snapShotJsonValue );

      /*Last mileage*/
      snapShotJsonValue.clear();
      snapShotJsonValue[DTC_DATA_ID] = CHJ_DIAG_DID_LAST_OCCUR_MILE;
      snapShotJsonValue[DTC_SNAPSHOT_FIELD_LAST_MILEAGE]= snapShot.lastMileage;
      json[DTC_DATA_FIELD_SNAPSHOT].append( snapShotJsonValue );

  }

  void CHJCarDiagDTCMonitor::checkAllDeviceStatus()
  {
      DTCERRORVALUE mRet = DTC_DISABLE;
      DTCERRORVALUE mValue;
      int32_t mDTCID = 0;

      AutoMutex _l( mDTCDeviceLock );
      for ( int i=0; i< static_cast<int>( mDevices.size()); i++ )
      {
          Device *pDevice = mDevices.valueAt( i );

          mRet = pDevice->checkStatus( mDTCID );

          //Disable DTC function, return.
          if ( mRet == DTC_DISABLE )
          {
              DIAG_D("%s:__ mRet =%d, mDTCID=%d__\n",__func__,mRet,mDTCID);
              return;
          }

          /*mRet has value, so check mDTCDevices
           1. This DTC exist in mDTCDevices, judge value is same as old value?
           2. This DTC does not exist in mDTCDevices, add value
           3. put DTC into JSON and send it to UDS
          */

          /*DTC ID is key, get index by DTC ID*/
          ssize_t idx = mDTCDevices.indexOfKey( pDevice->DTCID );
          if ( idx<0 && mRet == DTC_ACTIVE /*&& mDriverCircle==1 should add this case*/ )
          {
              /* idx<0 means that this DTC does not exist in mDTCDevices,
                 so add it into mDTCDevices.
                 Key is DTC ID, and value is current DTC_ACTIVE
               */

              mDTCDevices.add( pDevice->DTCID, mRet );

              /*TODO:packaging DTC message into JSON and send it to UDS*/
              std::string mMsg = packageJSONData( pDevice->DTCID, static_cast<int32_t>(mRet) );

              String8 mSendMsg = String8( mMsg.c_str() );

              DIAG_D("__checkAllDeviceStatus__ get JSONmSendMsg=%s",mSendMsg.c_str());

              if ( mListener != NULL )
              {
                  mListener->queueSendingMsg( mSendMsg );
              }
          }
          else if ( idx>=0 )
          {
              /*idx >=0 means that this device has happened DTC, so we need find it and clean it.
                Send message to UDS, tell it DTC DEACTIVED*/
              mValue = mDTCDevices.valueAt( idx );
              if ( mValue == DTC_ACTIVE && mRet==DTC_DEACTIVE )
              {
                  /*It means that DTC DEACTIVED,clean it*/
                  std::string mMsg = packageJSONData( pDevice->DTCID, static_cast<int32_t>(mRet) );
                  mDTCDevices.removeItem( pDevice->DTCID );

                  String8 mSendMsg = String8( mMsg.c_str() );


                  /*send this mMsg to UDS*/
                  if ( mListener != NULL )
                  {
                      mListener->queueSendingMsg( mSendMsg );
                  }

              }

          }
      }
  }

  /*Running in DTC Monitor Thread*/
  void CHJCarDiagDTCMonitor::loopMonitor()
  {
      /*1. Loop always
       *2. getEvent from HAL
       *3. judge fault one by one, <key,value> pairs store all devices
       *4. if one device fault, store it into another <key,value>pairs
       */

      if( mGroupClearAllDTC == true )
      {
          AutoMutex _l(mDTCDeviceLock);
          mDTCDevices.clear();
          DIAG_D("loopMonitor clear all DTC");
          mGroupClearAllDTC = false;
      }

      mDTCHal->trigerNeedQueryFuncs();

      checkAllDeviceStatus();

      mMonitorLooper->pollOnce( LOOP_TIMEOUT_MSECS );
  }


  /*set current power state from Car Power*/
/*
  PM_STATE_UNPOWERED = 0;
  PM_STATE_PARTLYWORK = 1;
  PM_STATE_NORMAL = 2;
  PM_STATE_PRESLEEP = 3;
  PM_STATE_SLEEP = 4;
  PM_STATE_ABNORMAL = 5;
*/
  void CHJCarDiagDTCMonitor::setDrivingCycleState( int state )
  {
      DIAG_D("%s:WDD cycle state=%d_\n",__func__,state);
      if ( state != mDriverCircle ) 
      {
          if ( mDriverCircle == 0 && state == DEM_CYCLE_STATE_START )
          {
              /*we recoding all DTC only in one driver circle.
               * Cleaning all DTC recording while one new driver circle.
              */
              AutoMutex _l(mDTCDeviceLock);
              mDTCDevices.clear();
          }

          mDriverCircle = state;
          String8 mSendMsg = String8( packagePowerStateJSONData( mDriverCircle ).c_str() );

          if ( mListener != NULL )
          {
              mListener->queueSendingMsg( mSendMsg );
          }
      }
  }


  int32_t CHJCarDiagDTCMonitor::getEthSQIValue()
  {
      return mDTCHal->getSQIValue();
  }

  int32_t CHJCarDiagDTCMonitor::getLinkStatus()
  {
      return mDTCHal->getLinkStatus();
  }

  int32_t CHJCarDiagDTCMonitor::getPhyId()
  {
      return mDTCHal->getPhyId();
  }

  int32_t CHJCarDiagDTCMonitor::getSQILimitValue()
  {
      return mDTCHal->getSQILimitValue();
  }

  void CHJCarDiagDTCMonitor::queryCableStatus()
  {
      mDTCHal->trigerCableStatusFuncs();
  }

  int32_t CHJCarDiagDTCMonitor::getCableStatus()
  {
      return mDTCHal->getCableStatus();
  }

  int32_t CHJCarDiagDTCMonitor::setSQILimitValue( int value )
  {
      if( value < 0x00 || value > 0xFF )
      {
          return -1;
      }
      
      return mDTCHal->setSQILimitValue( value );
  }

  int32_t CHJCarDiagDTCMonitor::setSQITestMode( int mode )
  {
      if( mode < 0x00 || mode > 0x07 )
      {
          return -1;
      }

      return mDTCHal->setSQITestMode( mode );
  }

  void CHJCarDiagDTCMonitor::resetPhyTestModeStatus()
  {
      mDTCHal->resetPhyTestMode();
  }

  void CHJCarDiagDTCMonitor::groupClearAllDTC()
  {
      if( !mGroupClearAllDTC )
      {
          mGroupClearAllDTC = true;
      }
  }

  /******************************Device*******************************************/
  CHJCarDiagDTCMonitor::Device::Device( const int32_t dtcId, 
                                          const int32_t deviceId, 
                                          boolDevFunc BoolDevFunc ):
                                          DTCID( dtcId ),
                                          deviceId( deviceId )
                                         
  {
      /*init value is true, enable check DTC*/
      enable = true;

      pBoolDevFunc = (BoolDevFunc!=NULL)?std::move(BoolDevFunc):NULL;
  
  }

  CHJCarDiagDTCMonitor::Device::~Device()
  {
  }

  DTCERRORVALUE CHJCarDiagDTCMonitor::Device::checkStatus(   int32_t& getDTCID )
  {
      DTCERRORVALUE retVal = DTC_DISABLE;

#if 1     
      /*DTC closed by UDS*/
      if ( !enable )
      {
          return retVal;
      }

      /*call function to check status*/
      if ( pBoolDevFunc != NULL )
      {
          if ( !pBoolDevFunc() )
          {
              retVal = DTC_ACTIVE;
          }
          else
          {
              retVal = DTC_DEACTIVE;
          }
          
      }

      getDTCID = DTCID;
#endif
      return retVal;
  }

  
}


