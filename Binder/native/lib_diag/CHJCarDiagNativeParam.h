#ifndef __CHJ_CAR_DIAG_NATIVE_PARAM_H__
#define __CHJ_CAR_DIAG_NATIVE_PARAM_H__

#include <utils/RefBase.h>
#include <vector>
#include <utils/String8.h>

namespace android
{
#define CHJDEBUG 0
    
#if CHJDEBUG
    #define LOG_TAG "DIAG.NATIVE"
    #define DIAG_I(...) ((void)ALOG(LOG_INFO, LOG_TAG, __VA_ARGS__))
    #define DIAG_E(...) ((void)ALOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))
    #define DIAG_D(...) ((void)ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))
    #define DIAG_W(...) ((void)ALOG(LOG_WARN, LOG_TAG, __VA_ARGS__))
#else
    #define DIAG_I(...)
    #define DIAG_E(...)
    #define DIAG_W(...)
    #define DIAG_D(...)
#endif /*CHJDEBUG*/


#define FREE_POINE(ptr) do{delete ptr; ptr=NULL;}while(0)
    
#define CHJ_DIAG_DTC_SUB_LCD_GMSL    17
#define CHJ_DIAG_DTC_MAIN_LCD_GMSL   18
#define CHJ_DIAG_DTC_BT_WIFI         21
#define CHJ_DIAG_DTC_MAIN_TUNER      22
#define CHJ_DIAG_DTC_SUB_TUNER       23
#define CHJ_DIAG_DTC_DSP             25
#define CHJ_DIAG_DTC_4G_COMM         44
#define CHJ_DIAG_DTC_MFI_COMM        75
#define CHJ_DIAG_DTC_MAIN_DISPLAY    80
#define CHJ_DIAG_DTC_SUB_DISPLAY     79
#define CHJ_DIAG_DTC_MAIN_TOUCH      78
#define CHJ_DIAG_DTC_SUB_TOUCH       77
#define CHJ_DIAG_DTC_LINK_LOSS       82
#define CHJ_DIAG_DTC_SQI_VALUE       83

#define CHJ_DIAG_DID_SYS_TIME        0x3300
#define CHJ_DIAG_DID_CUR_SYS_VOLT    0x3301
#define CHJ_DIAG_DID_BOARD_TEMP      0x3302
#define CHJ_DIAG_DID_SOC_TEMP        0x3303
#define CHJ_DIAG_DID_MOTOR_SPEED     0xF103
#define CHJ_DIAG_DID_VEHICLE_SPEED   0xF100
#define CHJ_DIAG_DID_LAST_OCCUR_MILE 0xF102


typedef enum 
{
    DTC_DISABLE = -1,
    DTC_DEACTIVE = 0,
    DTC_ACTIVE
}DTCERRORVALUE;


typedef enum
{
    LVDS_FAIL_FLAG = 0,
    POWER_FAIL_FLAG,
    SOURCE_FAIL_FLAG,
    GATE_FAIL_FLAG,
    NOCLK_FAIL_FLAG,
    EEPROM_FAIL_FLAG,
    LVDS_NO_FAIL,
    LVDS_CONNECT_FAIL,
    LVDS_FAIL_NOCLK_FAIL_FLAG
}DTC_SEC_DISPLAY_FAIL_DET;

typedef enum 
{
    HDMI_LVDS_FAIL_FLAG = 0,
    HDMI_POWER_FAIL_FLAG,
    HDMI_SOURCE_FAIL_FLAG,
    HDMI_GATE_FAIL_FLAG,
    HDMI_NO_VIDEO_FAIL_FLAG,
    HDMI_EEPROM_FAIL_FLAG,
    HDMI_OTP_TRIM_FAIL_FLAG,
    HDMI_CRC_FAIL_FLAG,
    HDMI_LVDS_NO_FAIL,
    HDMI_LVDS_CONNECT_FAIL,
    HDMI_LVDS_FAIL_NOCLK_FAIL_FLAG
}DTC_HDMI_DISPLAY_FAIL_DET;


typedef enum
{
    PM_STATE_UNPOWERED = 0,
    PM_STATE_PARTLYWORK,
    PM_STATE_NORMAL,
    PM_STATE_PRESLEEP,
    PM_STATE_SLEEP,
    PM_STATE_ABNORMAL
}DIAG_PM_STATE;

typedef enum
{
    DEM_CYCLE_STATE_START = 0,
    DEM_CYCLE_STATE_END,
    DEM_CYCLE_STATE_UNKNOW
}POWER_STATE;

const static char DTC_DATA_ID[] = "DataID";
const static char DTC_CLIENT[] = "client";
const static char DTC_CLIENT_DEM[] = "DEM";
const static char DTC_DATA_FIELD[] = "data";
const static char DTC_DATA_FIELD_METHOD[] = "method";
const static char DTC_DATA_FIELD_METHOD_DEM[] = "DEM_SetEventStatus";
const static char DTC_DATA_FIELD_EVENTNO[] = "eventNo";
const static char DTC_DATA_FIELD_STATUS[] = "status";
const static char DTC_DATA_FIELD_SNAPSHOT[] = "snapshot";
const static char DTC_SNAPSHOT_FIELD_SYSTIME[] = "SystemTime";
const static char DTC_SNAPSHOT_FIELD_VOLTAGE[] = "Voltage";
const static char DTC_SNAPSHOT_FIELD_BOARD_TEMP[] = "BoardTemperature";
const static char DTC_SNAPSHOT_FIELD_SOC_TEMP[] = "SOCTemperature";
const static char DTC_SNAPSHOT_FIELD_MOTOR_SPEED[] = "MotorSpeed";
const static char DTC_SNAPSHOT_FIELD_VEHICLE_SPEED[] = "VehicleSpeed";
const static char DTC_SNAPSHOT_FIELD_LAST_MILEAGE[] = "LastMileageInformation";
const static char METHOD_POWER_STATE_CYCLE_FIELD[] = "Dem_SetOperationCycleState";
const static char METHOD_POWER_STATE_CYCLE[] = "cycleState";

}

#endif /*__CHJ_CAR_DIAG_NATIVE_PARAM_H__*/
