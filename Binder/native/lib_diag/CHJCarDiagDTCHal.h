#ifndef __CHJ_CAR_DIAG_DTC_HAL__
#define __CHJ_CAR_DIAG_DTC_HAL__

#include "CHJCarDiagReader.h"
#include <hidl/Status.h>
#include <hidl/HidlSupport.h>
#include <mutex>

#include <android/hardware/fcdiagnose/1.0/IFcDiagnose.h>

namespace android
{
    using namespace android::hardware::fcdiagnose::V1_0;
    using namespace android::hardware;
    
    class  CHJCarDiagDTCHal: public virtual RefBase
    {
    public:
        CHJCarDiagDTCHal();
        ~CHJCarDiagDTCHal();

        void  trigerNeedQueryFuncs();
        void  trigerCableStatusFuncs();
        bool  getMainTpStatus(  );
        bool  getSecTpStatus();
        bool  getMainGmslStatus();
        bool  getSecGmslStatus();
        bool  getBtStatus();
        bool  getWifiStatus();
        bool  getBTWifiStatus();
        bool  getIpodStatus();
        bool  getMainTunerStatus();
        bool  getSecTunerStatus();
        bool  getDspStatus();
        bool  get4GStatus();
        bool  getMainDisplayStatus();
        bool  getSecDisplayStatus();
        bool getInsufficientSQIValue();
        bool getEthLinkUpStatus();

        int32_t getLinkStatus();
        int32_t getSQIValue();
        int32_t getPhyId();
        int32_t getSQILimitValue();
        int32_t setSQILimitValue( int32_t mode );
        int32_t setSQITestMode( int32_t mode );
        int32_t getCableStatus();
        void resetPhyTestMode();

     private:
        void getDiagData( DiagData data    );
        void getEthSQIValueCallbackFunc( EthData data );
        void getEthPhyIDCallbackFunc( EthData data );
        void getEthCableStatusCallbackFunc( EthData data );
        void getSQIWarnlimitCallbackFunc( EthData data );
        void onDTCHalDead(uint64_t cookie);
        void connectToDTChal();

         /*
          * For handling dtc hal service death while diag service lives on.
          */
             using OnDTCHalServiceDead = std::function<void(uint64_t)>;
             class DTCHalDeathRecipient : public hidl_death_recipient 
             {
             public:
                 DTCHalDeathRecipient(const OnDTCHalServiceDead& onHalServiceDead)
                     :mDTCHalServiceDead(onHalServiceDead){}
                 virtual ~DTCHalDeathRecipient() = default;
                 virtual void serviceDied(uint64_t cookie,
                                          const wp<::android::hidl::base::V1_0::IBase>& /* who */) override 
                 {
                     mDTCHalServiceDead(cookie);
                 }
             private:
                 OnDTCHalServiceDead mDTCHalServiceDead;
             };
             
        sp<IFcDiagnose> mFcDiagnoseHAL;
        sp<DTCHalDeathRecipient> mDTCHalDeathRecipient;
        android::hardware::fcdiagnose::V1_0::IFcDiagnose::getDiagData_cb DTCHalCallback;
        android::hardware::fcdiagnose::V1_0::IFcDiagnose::getEthSQIValue_cb getEthSQIValueCallback;
        android::hardware::fcdiagnose::V1_0::IFcDiagnose::getPhyID_cb getEthPhyIdCallback;
        android::hardware::fcdiagnose::V1_0::IFcDiagnose::getEthCableStatus_cb getEthCableStatusCallback;
        android::hardware::fcdiagnose::V1_0::IFcDiagnose::getSqiWarnlimit_cb getSQIWarnLimitCallback;
        bool mMainDisplayStatus;
        bool mSecDisplayStatus;
        int32_t mEthSQIvalue;
        int32_t mPhyID;
        int32_t mEthSQIwarnlimit;
        int32_t mEthCablestatus;
        bool mEthLinkLoss;
        std::mutex mDiagDataMutex;
        std::mutex mPhyIDMutex;
        std::mutex mSQIValueMutex;
    };

}
#endif //__CHJ_CAR_DIAG_DTC_HAL__
