LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ROOT_DIR := ../../../../../../

LOCAL_C_INCLUDES += \
    $(ROOT_DIR)system/core/libutils/include

LOCAL_SRC_FILES:= \
    $(ROOT_DIR)packages/services/Car/car-lib/src/android/car/ICar.aidl \
    $(ROOT_DIR)packages/services/Car/car-lib/src/com/tsdl/car/power/IAlarmTimerCb.aidl \
    $(ROOT_DIR)packages/services/Car/car-lib/src/com/tsdl/car/power/ICarPowerManager.aidl \
    $(ROOT_DIR)packages/services/Car/car-lib/src/com/tsdl/car/power/IPowerEventListener.aidl \
    $(ROOT_DIR)packages/services/Car/car-lib/src/com/tsdl/car/power/IPowerRebootListener.aidl \
    CarPowerManager.cpp

LOCAL_SHARED_LIBRARIES:= \
    libbinder \
    liblog \
    libutils

LOCAL_CFLAGS += \
    -Wall \
    -Wextra \
    -Werror \
    -Wno-unused-parameter

LOCAL_AIDL_INCLUDES := packages/services/Car/car-lib/src

LOCAL_MODULE_PATH_64 := $(TARGET_OUT_VENDOR)/lib64
LOCAL_MODULE_PATH_32 := $(TARGET_OUT_VENDOR)/lib
LOCAL_MULTILIB := both
LOCAL_MODULE := libcarpowermanager
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
