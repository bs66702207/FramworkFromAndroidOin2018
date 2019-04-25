LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    com_tsdl_car_power_PowerStateMachineImpl.cpp

LOCAL_MODULE_PATH_64 := $(TARGET_OUT)/lib64
LOCAL_MODULE_PATH_32 := $(TARGET_OUT)/lib
LOCAL_MULTILIB := both
LOCAL_MODULE := libchjsuspend-jni
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

LOCAL_MODULE_TAGS := optional
LOCAL_PROGUARD_ENABLED := disabled

LOCAL_SHARED_LIBRARIES := \
    libandroid_runtime \
    libnativehelper \
    libbinder \
    libcutils \
    libutils \
    liblog \
    libhardware \
    libbase \
    libhardware_legacy \
    libhidlbase \
    libsuspend \

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE)

#LOCAL_CPPFLAGS += "-Wno-reserved-user-defined-literal"
include $(BUILD_SHARED_LIBRARY)
