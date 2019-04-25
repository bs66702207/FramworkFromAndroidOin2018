LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    com_android_car_chj_CHJCarDiagService.cpp

LOCAL_MODULE_PATH_64 := $(TARGET_OUT)/lib64
LOCAL_MODULE_PATH_32 := $(TARGET_OUT)/lib
LOCAL_MULTILIB := both
LOCAL_MODULE := libchjcar-jni
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
    libchjcar_diag_native \
    libhwbinder \
    android.hardware.fcdiagnose@1.0 \
    android.hardware.automotive.vehicle@2.0

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE)

LOCAL_STATIC_LIBRARIES := libjsoncpp

#LOCAL_CPPFLAGS += "-Wno-reserved-user-defined-literal"
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE       := init.chj.diag.rc
LOCAL_MODULE_TAGS  := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES    := ./init.chj.diag.rc
LOCAL_MODULE_PATH  := $(TARGET_OUT_VENDOR_ETC)/init/
include $(BUILD_PREBUILT)
