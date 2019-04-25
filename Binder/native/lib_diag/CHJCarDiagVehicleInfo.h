#ifndef __CHJ_CAR_DIAG_VEHICLE_INFO_H__
#define __CHJ_CAR_DIAG_VEHICLE_INFO_H__

#include "CHJCarDiagDTCHal.h"

#include <hidl/Status.h>
#include <hidl/HidlSupport.h>

#include <android/hardware/automotive/vehicle/2.0/IVehicle.h>
#include <android/hardware/automotive/vehicle/2.0/types.h>

namespace android
{
    using namespace ::android::hardware::automotive::vehicle::V2_0;
    using namespace android::hardware;

    class CHJCarDiagVehicleInfo : public virtual RefBase
    {
      public:
        
           CHJCarDiagVehicleInfo(  );
        
           ~CHJCarDiagVehicleInfo();
         

           typedef struct vehicleSnapShotStr
           {
               std::vector<int32_t> sysTime;
               int socCurTemp;
               float boardCurTemp;
               float sysCurVolt;
               float curMotorSpeed;
               float curVehicleSpeed;
               int lastMileage;
           }vehicleSnapShotStr;

           void getCurVehicleSnapShotInfo(      vehicleSnapShotStr *snapShotInfo );
           
      private:
              void onVHALDead(uint64_t cookie);
          /*
           * For handling vhal  death while diag service lives on.
           */
              using OnVHALServiceDead = std::function<void(uint64_t)>;
              class VHALDeathRecipient : public hidl_death_recipient 
              {
               public:
                  VHALDeathRecipient(const OnVHALServiceDead& onVHALServiceDead)
                      :mVHALServiceDead(onVHALServiceDead){}
                  virtual ~VHALDeathRecipient() = default;
                  virtual void serviceDied(uint64_t cookie,
                                              const wp<::android::hidl::base::V1_0::IBase>& /* who */) override 
                  {
                      mVHALServiceDead(cookie);
                  }
                                              
              private:
                  OnVHALServiceDead mVHALServiceDead;
              };
              
          void connectToVHAL();
          void queryInfoToMCU( int8_t queryId );

          void getSysTime( std::vector<int32_t> &timeValue );
          void getSoCTemperature( int &SocTemp );
          void getBoardTemperature( float &boardTemp );
          void getSysVoltage( float &sysVolt );
          void getVehicleMotorSpeed( float &engineSpeed );
          void getVehicleSpeed(     float &speed  );
          void getLastMileageInfo( int &mile );
          
          sp<IVehicle> mVehicleHal;
          sp<VHALDeathRecipient> mVHALDeathRecipient;
    };
}


#endif /*__CHJ_CAR_DIAG_VEHICLE_INFO_H__*/
