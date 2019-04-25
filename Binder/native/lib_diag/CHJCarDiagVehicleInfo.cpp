/*wrapper vhal*/

#include "CHJCarDiagVehicleInfo.h"
#include <time.h>

#include <stdlib.h>

namespace android
{

  #define VEHILCE_SPEED_USED
  #define VEHICLIE_ENGINE_SPEED_USED
  #define VEHICLE_TOTAL_ODOMETER_USED

  using ::android::hardware::automotive::vehicle::V2_0::VehicleProperty;

  static constexpr uint64_t kVHALDiedCookie = 0;
  const int mQueryCommandList[] ={0x03,0x08,0x0A,0x0D};  //0D need change to A0 2018-11-07
  const int LOWMASK = 0x0000FFFF;

  CHJCarDiagVehicleInfo::CHJCarDiagVehicleInfo():
    mVHALDeathRecipient( new VHALDeathRecipient(
                         std::bind(&CHJCarDiagVehicleInfo::onVHALDead, this, std::placeholders::_1)))
  {

      /*connect to vhal*/
      mVehicleHal = IVehicle::getService();
      if ( mVehicleHal.get() == nullptr )
      {
          DIAG_E("%s: Can't connect to VHAL", __func__);
      }
      else
      {
          mVehicleHal->linkToDeath( mVHALDeathRecipient, kVHALDiedCookie );
      }
  }

  CHJCarDiagVehicleInfo::~CHJCarDiagVehicleInfo()
  {
  }

  void CHJCarDiagVehicleInfo::queryInfoToMCU( int8_t queryId )
  {
      StatusCode returnStatusCode = StatusCode::TRY_AGAIN;

      if( mVehicleHal.get() == nullptr )
      {
          return;
      }

      /*query all*/
      if ( queryId == -1 )
      {
          /*JAVA has been queried all, maybe we do not query all again*/
      }
      else
      {
         VehiclePropValue queryPropValue;
         queryPropValue.prop = static_cast<int32_t>( VehicleProperty::CHJ_W_MCU_QUERY_INFO );
         queryPropValue.value.int32Values.resize(1);
         queryPropValue.value.int32Values[0] = static_cast<int32_t>( mQueryCommandList[queryId] );


         returnStatusCode = mVehicleHal->set( queryPropValue );
         if ( returnStatusCode != StatusCode::OK )
         {
             DIAG_D(" queryInfoToMCU failed set! status code:%d \n", returnStatusCode);
         }
         else
         {
             DIAG_D(" queryInfoToMCU success set!");
         }

         /*TODO:maybe add return code to invoker*/
      }
  }

  void CHJCarDiagVehicleInfo::getVehicleMotorSpeed( float &engineSpeed )
  {
#ifdef VEHICLIE_ENGINE_SPEED_USED
      VehiclePropValue propValue;
      
      StatusCode statusCodeValue = StatusCode::TRY_AGAIN;
      
      if( mVehicleHal.get() == nullptr )
      {
          return;
      }

      propValue.prop = static_cast<int32_t>( VehicleProperty::CHJ_R_EMS_ENGINE_SPEED );
      propValue.areaId = 0;

      bool called = false;

      hardware::Return<void> _hidl_status;
      _hidl_status = mVehicleHal->get( propValue,[&propValue, &statusCodeValue, &called]( StatusCode s, const VehiclePropValue &value)
                       {
                           statusCodeValue = s;
                           propValue = value;
                           called = true;
                       });

      if( !_hidl_status.isOk() || statusCodeValue != StatusCode::OK)
      {
          engineSpeed = 0.0f;

          DIAG_D("%s:getVehicleMotorSpeed can not get value form vhal=%f__\n",__func__,engineSpeed);
          return;
      }

      engineSpeed = propValue.value.floatValues[0];

#else

      engineSpeed = 0.0f;

#endif
  }

  void CHJCarDiagVehicleInfo::getVehicleSpeed( float &speed )
  {
#ifdef VEHILCE_SPEED_USED
      VehiclePropValue propValue;

      StatusCode statusCodeValue = StatusCode::TRY_AGAIN;

      if( mVehicleHal.get() == nullptr )
      {
          return;
      }

      propValue.prop = static_cast<int32_t>( VehicleProperty::ESP_VehicleSpeed );
      propValue.areaId = 0;

      bool called = false;

      hardware::Return<void> _hidl_status;
      _hidl_status = mVehicleHal->get( propValue,[&propValue, &statusCodeValue, &called]( StatusCode s, const VehiclePropValue &value)
                       {
                           statusCodeValue = s;
                           propValue = value;
                           called = true;
                       });

      if( !_hidl_status.isOk() || statusCodeValue != StatusCode::OK)
      {
          speed = 0.0f;

          DIAG_D("%s:_getVehicleSpeed can not get value form vhal=%f__\n",__func__,speed);
          return;
      }

      speed = propValue.value.floatValues[0];
#else
      speed = 0.0f;
      DIAG_D("%s:_getVehicleSpeed =%f__\n",__func__,speed);
#endif
  }

  void CHJCarDiagVehicleInfo::getLastMileageInfo( int &mile )
  {
#ifdef VEHICLE_TOTAL_ODOMETER_USED  
      VehiclePropValue propValue;
      StatusCode statusCodeValue = StatusCode::TRY_AGAIN;
          
      if ( mVehicleHal.get() == nullptr )
      {
          return;
      }
          
      propValue.prop = static_cast<int32_t>( VehicleProperty::IPC_TotalOdometer );
      propValue.areaId = 0;
          
      bool called = false;
          
      hardware::Return<void> _hidl_status;
      _hidl_status = mVehicleHal->get( propValue,[&propValue, &statusCodeValue, &called]( StatusCode s, const VehiclePropValue &value)
                       {
                           statusCodeValue = s;
                           propValue = value;
                           called = true;
                       });

      if( !_hidl_status.isOk() || statusCodeValue != StatusCode::OK)
      {
          mile = 0;
          return;
      }

      mile = propValue.value.int32Values[0];
#else

      mile = 0;

#endif //VEHICLE_TOTAL_ODOMETER_USED
  }

  void CHJCarDiagVehicleInfo::getBoardTemperature( float &boardTemp )
  {
      VehiclePropValue propValue;

      StatusCode statusCodeValue = StatusCode::TRY_AGAIN;

      if ( mVehicleHal.get() == nullptr )
      {
          return;
      }

      propValue.prop = static_cast<int32_t>( VehicleProperty::CHJ_R_MCU_NAVI_TEMPERATURE );
      propValue.areaId = 0;

      bool called = false;

      hardware::Return<void> _hidl_status;

      _hidl_status = mVehicleHal->get( propValue,[&propValue, &statusCodeValue, &called]( StatusCode s, const VehiclePropValue &value)
                       {
                           statusCodeValue = s;
                           propValue = value;
                           called = true;
                       });

      if( !_hidl_status.isOk() || statusCodeValue != StatusCode::OK)
      {
          boardTemp = 0.0f;
          return;
      }

      boardTemp = propValue.value.floatValues[0];
      //DIAG_D("%s:_getBoardTemperature_board temperature=%f__\n",boardTemperatureValue);
  }

  void CHJCarDiagVehicleInfo::getSysVoltage( float &sysVolt )
  {

      if( mVehicleHal.get() == nullptr )
      {
          return;
      }

      queryInfoToMCU( mQueryCommandList[1] );

      //usleep( 40 );

      VehiclePropValue propValue;

      StatusCode statusCodeValue = StatusCode::TRY_AGAIN;

      propValue.prop = static_cast<int32_t>( VehicleProperty::CHJ_R_MCU_CUR_VOLTAGE_STATE );
      propValue.areaId = 0;

      bool called = false;

      hardware::Return<void> _hidl_status;
      _hidl_status = mVehicleHal->get( propValue,[&propValue, &statusCodeValue, &called]( StatusCode s, const VehiclePropValue &value)
                       {
                           statusCodeValue = s;
                           propValue = value;
                           called = true;
                       });

      if( !_hidl_status.isOk() || statusCodeValue != StatusCode::OK)
      {
          sysVolt = 0.0f;
          return;
      }

      sysVolt = (float)(propValue.value.int32Values[0]&LOWMASK)*0.001f;
  }

  void CHJCarDiagVehicleInfo::getSoCTemperature( int &SoCTemp )
  {

      if( mVehicleHal.get() == nullptr )
      {
          return;
      }

      int fd = open( "/sys/class/thermal/thermal_zone0/temp" , O_RDONLY );
      if ( fd <0 )
      {
          DIAG_E("Unable to open thermal_zone");
          SoCTemp = 0;
          return;
      }


      char buffer[5];
      memset( buffer, 0, 5 );
      const int len = read(fd, buffer, sizeof(buffer)-1);
      close(fd);


      SoCTemp = atoi( buffer );

      //DIAG_D("%s: getSoCtemp value=%d__\n",__func__,SoCTemp);

  }


  void CHJCarDiagVehicleInfo::getSysTime( std::vector<int32_t> &timeValue )
  {
      time_t rawTime;
      struct tm *pTmInfo = NULL;

      time( &rawTime );

      pTmInfo = localtime( &rawTime );

      if ( pTmInfo != NULL )
      {
          timeValue.push_back( pTmInfo->tm_year+1900 );  //year
          timeValue.push_back( pTmInfo->tm_mon+1 );
          timeValue.push_back( pTmInfo->tm_mday );
          timeValue.push_back( pTmInfo->tm_hour );
          timeValue.push_back( pTmInfo->tm_min );
          timeValue.push_back( pTmInfo->tm_sec );
      }
      else
      {
         timeValue.clear();
      }

  }


  void CHJCarDiagVehicleInfo::getCurVehicleSnapShotInfo( vehicleSnapShotStr *snapShotInfo )
  {
      getSysTime( snapShotInfo->sysTime );
      getSysVoltage( snapShotInfo->sysCurVolt );
      getSoCTemperature( snapShotInfo->socCurTemp );
      getBoardTemperature( snapShotInfo->boardCurTemp );
      getVehicleMotorSpeed( snapShotInfo->curMotorSpeed );
      getVehicleSpeed( snapShotInfo->curVehicleSpeed );
      getLastMileageInfo( snapShotInfo->lastMileage );
  }


  void CHJCarDiagVehicleInfo::connectToVHAL()
  {
      DIAG_D("%s Enter", __func__);

      sleep(2);

      mVehicleHal = IVehicle::getService();
      if (mVehicleHal.get() == nullptr)
      {
          ALOGE("Can't reconnect to DTC-HAL");
      }
      else
      {
          mVehicleHal->linkToDeath( mVHALDeathRecipient, kVHALDiedCookie );
      }
  }

  void CHJCarDiagVehicleInfo::onVHALDead(uint64_t cookie)
  {
      switch (cookie)
      {
      case kVHALDiedCookie:
              DIAG_D("V-HAL was dead! try to reconnect");
              auto ret = mVehicleHal->unlinkToDeath(mVHALDeathRecipient);
              if (!ret.isOk())
              {
                  DIAG_E("%s failed to unlink to death, client: %p, err: %s",
                        __func__, mVehicleHal.get(), ret.description().c_str());
              }
              mVehicleHal = nullptr;

              // reconnect
              connectToVHAL();
          break;
      }
  }


}
