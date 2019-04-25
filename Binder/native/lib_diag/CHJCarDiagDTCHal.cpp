#include "CHJCarDiagDTCHal.h"

namespace android
{
    static constexpr uint64_t kVhalDiedCookie = 0;
    
    CHJCarDiagDTCHal::CHJCarDiagDTCHal():
        mDTCHalDeathRecipient(new DTCHalDeathRecipient(
        std::bind(&CHJCarDiagDTCHal::onDTCHalDead, this, std::placeholders::_1)))
    {
        mFcDiagnoseHAL = IFcDiagnose::getService();
        if ( mFcDiagnoseHAL.get() == nullptr )
        {
            DIAG_E("can not get DTC HAL service");
        }
        else
        {
            mFcDiagnoseHAL->linkToDeath( mDTCHalDeathRecipient, kVhalDiedCookie );

            /*bind HAL service callback*/
            DTCHalCallback = std::bind( &CHJCarDiagDTCHal::getDiagData, this, std::placeholders::_1 );
            getEthCableStatusCallback = std::bind( &CHJCarDiagDTCHal::getEthCableStatusCallbackFunc, this, std::placeholders::_1 );
            getEthPhyIdCallback = std::bind( &CHJCarDiagDTCHal::getEthPhyIDCallbackFunc, this, std::placeholders::_1 );
            getEthSQIValueCallback = std::bind( &CHJCarDiagDTCHal::getEthSQIValueCallbackFunc, this, std::placeholders::_1  );
            getSQIWarnLimitCallback = std::bind( &CHJCarDiagDTCHal::getSQIWarnlimitCallbackFunc, this, std::placeholders::_1 );
        }

        mMainDisplayStatus = mSecDisplayStatus = true;
        mEthSQIvalue = -1;
        mEthSQIwarnlimit = -1;
        mPhyID = 0xFF;
        mEthCablestatus = 0;
        mEthLinkLoss = false;
    }

    CHJCarDiagDTCHal::~CHJCarDiagDTCHal()
    {
    }

   void CHJCarDiagDTCHal::trigerNeedQueryFuncs()
   {
       hardware::Return<void> _hidl_status;

       if(  mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           _hidl_status = mFcDiagnoseHAL->getEthSQIValue( getEthSQIValueCallback );
           if( !_hidl_status.isOk() )
           {
               mEthSQIvalue = -1;
               DIAG_E("%s: getEthSQIValue callback failed",__func__);
           }

           _hidl_status = mFcDiagnoseHAL->getPhyID( getEthPhyIdCallback );
           if( !_hidl_status.isOk() )
           {
                mPhyID = -1;
                DIAG_E("%s: getPhyID callback failed",__func__);
           }

           _hidl_status = mFcDiagnoseHAL->getSqiWarnlimit( getSQIWarnLimitCallback );
           if( !_hidl_status.isOk() )
           {
               mEthSQIwarnlimit = -1;
               DIAG_E("%s: mEthSQIwarnlimit callback failed",__func__);
           }
       }
   }

   void CHJCarDiagDTCHal::trigerCableStatusFuncs()
   {
       hardware::Return<void> _hidl_status;
       DIAG_D("%s: start triger cable status",__func__);
       _hidl_status = mFcDiagnoseHAL->getEthCableStatus( getEthCableStatusCallback );
       if( !_hidl_status.isOk() )
       {
           mEthCablestatus = -1;
       }
   }

   void CHJCarDiagDTCHal::getEthSQIValueCallbackFunc( EthData data )
   {
       mEthSQIvalue = -1;
       if(  mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           std::lock_guard<std::mutex> lock( mSQIValueMutex );
           mEthSQIvalue = data.EthSQIvalue;
       }
   }

   void CHJCarDiagDTCHal::getEthPhyIDCallbackFunc( EthData data )
   {
       mPhyID = -1;
       if(  mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           std::lock_guard<std::mutex> lock( mPhyIDMutex );
           mPhyID = data.PHY_ID;
       }
   }

   void CHJCarDiagDTCHal::getEthCableStatusCallbackFunc( EthData data )
   {
       mEthCablestatus = -1;
       if(  mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           mEthCablestatus = data.EthCablestatus;
           DIAG_D(" WDD getEthCableStatusCallbackFunc mEthCablestatus=%d",mEthCablestatus);
       }
   }

   void CHJCarDiagDTCHal::getSQIWarnlimitCallbackFunc( EthData data )
   {
       mEthSQIwarnlimit = -1;
       if(  mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           mEthSQIwarnlimit = data.EthSQIwarnlimit;
       }
   }

   bool CHJCarDiagDTCHal::getEthLinkUpStatus()
   {
       mEthLinkLoss = true;

       if(  mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
          Return<bool> _hidl_bool = mFcDiagnoseHAL->getEthLinkupStatus();
          if( !_hidl_bool.isOk() )
          {
              DIAG_E("get Link status failured");
              mEthLinkLoss = true;
          }
          else
          {
              mEthLinkLoss = (bool)_hidl_bool;
              DIAG_D("getEthLinkUpStatus  mEthLinkLoss=%d",mEthLinkLoss);
          }
       }
       return mEthLinkLoss;
   }

   bool CHJCarDiagDTCHal::getInsufficientSQIValue()
   {
       if( mEthSQIvalue == -1 ||
           mEthSQIwarnlimit == -1)
       {
           return true;
       }

       DIAG_D("getInsufficientSQIValue mEthSQIvalue=%d,mEthSQIwarnlimit=%d",mEthSQIvalue,mEthSQIwarnlimit);
       return ( mEthSQIvalue < mEthSQIwarnlimit ) ? false : true;
   }

   int32_t CHJCarDiagDTCHal::getLinkStatus()
   {
       int32_t res = -1;

       if(  mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
          Return<bool> _hidl_bool = mFcDiagnoseHAL->getEthLinkupStatus();
          if( !_hidl_bool.isOk() )
          {
              DIAG_E("get Link status failured");
              res = -1;
          }
          else
          {
              res = (bool)_hidl_bool? 1 : 0;
              DIAG_D("getLinkStatus res=%d",res);
          }
       }

       return res;
   }

   int32_t CHJCarDiagDTCHal::getSQIValue()
   {
       if( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           std::lock_guard<std::mutex> lock( mSQIValueMutex );
           return mEthSQIvalue;
       }

       return -1;
   }

   int32_t CHJCarDiagDTCHal::getPhyId()
   {
       if( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           std::lock_guard<std::mutex> lock( mPhyIDMutex );
           return mPhyID;
       }

       return -1;
   }

   int32_t CHJCarDiagDTCHal::getSQILimitValue()
   {
       if( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           return mEthSQIwarnlimit;
       }

       return -1;
   }

   int32_t CHJCarDiagDTCHal::setSQILimitValue( int32_t mode )
   {
       if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           FcDiagnoseValue valueStr;
           valueStr.SetSQIwarnlimit = mode;

           DIAG_D("set SQI limit value:%d",mode);
           Return<void> _hidl_status = mFcDiagnoseHAL->setSqiWarnlimit( valueStr );
           if( !_hidl_status.isOk() )
           {
               DIAG_E("%s: setSQILimitValue HIDL failed",__func__);
               return -1;
           }

           _hidl_status = mFcDiagnoseHAL->getSqiWarnlimit( getSQIWarnLimitCallback );
           if( !_hidl_status.isOk() )
           {
               mEthSQIwarnlimit = -1;
               DIAG_E("%s: mEthSQIwarnlimit callback failed",__func__);
           }
       }
       else
       {
           DIAG_E("%s:can not setSQILimitValuee",__func__);
           return -1;
       }

       return 0;
   }

   int32_t CHJCarDiagDTCHal::setSQITestMode( int32_t mode )
   {
       if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
       {
           FcDiagnoseValue modeStr;
           modeStr.Settestmode = mode;
           Return<void> _hidl_status = mFcDiagnoseHAL->setTestMode( modeStr );
           if( !_hidl_status.isOk() )
           {
               DIAG_E("%s: setSQITestMode HIDL failed",__func__);
               return -1;
           }
       }
       else
       {
           DIAG_E("%s:can not setTestMode",__func__);
           return -1;
       }

       return 0;
   }

    bool CHJCarDiagDTCHal::getMainTpStatus(  )
    {
        bool ret = false;
        
        hardware::Return<void> _hidl_void;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           //ret = mFcDiagnoseHAL->getMainTpStatus();
           Return<bool> _hidl_status = mFcDiagnoseHAL->getMainTpStatus();
           if( !_hidl_status.isOk() )
           {
               ret = true;
           }
           else
           {
               ret = (bool)_hidl_status;
               DIAG_D("getMainTPStatus ret=%d\n",ret);
           }

           /*check main and second display*/
           _hidl_void = mFcDiagnoseHAL->getDiagData( DTCHalCallback );
           if( ! _hidl_void.isOk() )
           {
               mSecDisplayStatus = true;
               mMainDisplayStatus = true;
           }
        }
        else
        {
            DIAG_E("%s:can not get DTC HAL MainTP device",__func__);
        }
        
        return ret;
    }
    
    bool  CHJCarDiagDTCHal::getSecTpStatus()
    {
        bool ret = false;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getSecTpStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get second tp status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
           DIAG_D("getSecTpStatus ret=%d\n",ret);
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }
    
    bool  CHJCarDiagDTCHal::getMainGmslStatus()
    {
        bool ret = true;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getMainGmslStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get main Gmsl status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }
    
    bool  CHJCarDiagDTCHal::getSecGmslStatus()
    {
        bool ret = true;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getSecGmslStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get sec Gmsl status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }
    
    bool CHJCarDiagDTCHal::getBtStatus()
    {
        bool ret = false;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getBtStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get bt status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }
    
    bool  CHJCarDiagDTCHal::getWifiStatus()
    {
        bool ret = false;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getWifiStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get wifi status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }

    bool  CHJCarDiagDTCHal::getBTWifiStatus()
    {
        bool ret = getWifiStatus() || getBtStatus();
        return ret;
    }
    
    bool  CHJCarDiagDTCHal::getIpodStatus()
    {
        bool ret = false;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getIpodStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get Ipod status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
           DIAG_D("%s: get Ipod status:%d",__func__,ret);
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }
    
    bool  CHJCarDiagDTCHal::getMainTunerStatus()
    {
        bool ret = false;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getMainTunerStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get main tuner status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }
    
    bool  CHJCarDiagDTCHal::getSecTunerStatus()
    {
        bool ret = false;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getSecTunerStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get sec tuner status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }
    
    bool  CHJCarDiagDTCHal::getDspStatus()
    {
        bool ret = false;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->getDspStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get DSP status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }
    
    bool CHJCarDiagDTCHal::get4GStatus()
    {
        bool ret = false;
        
        if ( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
           Return<bool> _hidl_bool = mFcDiagnoseHAL->get4GStatus();
           if( ! _hidl_bool.isOk() )
           {
               DIAG_D("%s: get 4G status HIDL failed",__func__);
               return ret;
           }

           ret = (bool)_hidl_bool;
        }
        else
        {
            DIAG_E("can not get %s device",__func__);
        }
        
        return ret;
    }

    bool  CHJCarDiagDTCHal::getMainDisplayStatus()
    {
        std::lock_guard<std::mutex> lock( mDiagDataMutex );
        DIAG_D("getMainDisplayStatus =%d",mMainDisplayStatus);
        return mMainDisplayStatus;
    }
    
    bool  CHJCarDiagDTCHal::getSecDisplayStatus()
    {
       DIAG_D("getSecDisplayStatus=%d",mSecDisplayStatus);
        return mSecDisplayStatus;
    }

    void CHJCarDiagDTCHal::getDiagData( DiagData data  )
    {
        std::lock_guard<std::mutex> lock( mDiagDataMutex );

        /*ture is normal, false is failed*/
        DIAG_D("getDiagData data.main_displayhealth=%d",data.main_displayhealth);
        DIAG_D("getDiagData data.sec_displayhealth=%d",data.sec_displayhealth);

        mMainDisplayStatus = (data.main_displayhealth != HDMI_LVDS_NO_FAIL)?false:true;
        mSecDisplayStatus = (data.sec_displayhealth != LVDS_NO_FAIL)?false:true;
    }

    int32_t CHJCarDiagDTCHal::getCableStatus()
    {
        if( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
            DIAG_D(" WDD getCableStatus mEthCablestatus=%d",mEthCablestatus);
            return mEthCablestatus;
        }
        
        return -1;
    }

    void CHJCarDiagDTCHal::connectToDTChal()
    {
        DIAG_D("%s Enter", __func__);

        sleep(2);
    
        mFcDiagnoseHAL = IFcDiagnose::getService();
        if (mFcDiagnoseHAL.get() == NULL) 
        {
            ALOGE("Can't reconnect to DTC-HAL");
        } 
        else
        {
            mFcDiagnoseHAL->linkToDeath(mDTCHalDeathRecipient, kVhalDiedCookie);
        }
    }

    void CHJCarDiagDTCHal::resetPhyTestMode()
    {
        if( mFcDiagnoseHAL != nullptr && mFcDiagnoseHAL.get() != nullptr )
        {
            DIAG_D(" WDD resetPhyTestMode");

            Return<void> _hidl_status = mFcDiagnoseHAL->reset_testmode();
            if( !_hidl_status.isOk() )
            {
                DIAG_D(" WDD resetPhyTestMode failure");
                return;
            }

            DIAG_D("WDD reset sucess");
        }
    }

    void CHJCarDiagDTCHal::onDTCHalDead(uint64_t cookie)
    {
        switch (cookie) 
        {
        case kVhalDiedCookie:
                DIAG_D("DTC-HAL was dead! try to reconnect");
                auto ret = mFcDiagnoseHAL->unlinkToDeath(mDTCHalDeathRecipient);
                if (!ret.isOk()) 
                {
                    DIAG_E("%s failed to unlink to death, client: %p, err: %s",
                          __func__, mFcDiagnoseHAL.get(), ret.description().c_str());
                }
                mFcDiagnoseHAL = nullptr;
                
                // reconnect
                connectToDTChal();
            break;
        }
    }

}
