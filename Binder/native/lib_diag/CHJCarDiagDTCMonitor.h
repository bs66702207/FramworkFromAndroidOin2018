#ifndef __CHJ_CAR_DIAG_DTC_MONITOR_H__
#define __CHJ_CAR_DIAG_DTC_MONITOR_H__


#include <utils/Looper.h>
#include <utils/Timers.h>
#include <mutex>
#include <json/json.h>

#include "CHJCarDiagVehicleInfo.h"


namespace android
{
   
    class CHJCarDiagDTCMonitor : public virtual RefBase
    {
     public:
        CHJCarDiagDTCMonitor( const sp<CHJCarDiagReaderInterface>&mPtrDiagService,   const sp<CHJCarDiagReader>& listener );
    
        ~CHJCarDiagDTCMonitor();
    
        void loopMonitor();

        void startDriveCircle();
        void stopDriveCircle();
        void setDrivingCycleState(int state);

        void queryCableStatus();
        int32_t getEthSQIValue();
        int32_t getLinkStatus();
        int32_t getPhyId();
        int32_t getSQILimitValue();
        int32_t setSQILimitValue( int value );
        int32_t setSQITestMode( int mode );
        int32_t getCableStatus();
        void resetPhyTestModeStatus();
        void groupClearAllDTC();
        
     private:

         using boolDevFunc = std::function<bool(void)>;

         struct Device
         {

             const int32_t DTCID;
             const int deviceId;
             nsecs_t when;
             boolDevFunc pBoolDevFunc;
         
             Device( const int32_t dtcId, const int32_t deviceId, 
                       boolDevFunc BoolDevFunc );
             ~Device();
             DTCERRORVALUE checkStatus(   int32_t& getDTCID);
             bool enable;
         };


        int testSocket();
        void addDeviceLocked();
        void clearAllDeviceLocked();
        void clearDeviceLocked( Device *pDevice );
        void checkAllDeviceStatus();
        std::string packageJSONData( int32_t DTCId, int32_t status );
        std::string packagePowerStateJSONData( int32_t status );
        void handleSnapShotInfo( Json::Value &json, CHJCarDiagVehicleInfo::vehicleSnapShotStr &snapShot );
        
     private:
        Mutex mDTCDeviceLock;
        sp<Looper> mMonitorLooper;
        int mDriverCircle;                                 //0 is start, 1 is end, default is -1
        int mDEMPowerState;                                //inform UDS current power state
        sp<CHJCarDiagReaderInterface> mNativeDiagService;
        sp<CHJCarDiagReader> mListener;
        int32_t mNextDeviceId;
        std::atomic<bool> mGroupClearAllDTC;
        KeyedVector<int32_t, Device*> mDevices;            //all devices
        KeyedVector<int32_t, DTCERRORVALUE>mDTCDevices;    //DTC devices
        sp<CHJCarDiagDTCHal> mDTCHal;
        sp<CHJCarDiagVehicleInfo> mVehicleInfo;
    };
    
}

#endif //__CHJ_CAR_DIAG_DTC_MONITOR_H__
