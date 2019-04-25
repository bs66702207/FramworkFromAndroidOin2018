LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE_PATH_64 := $(TARGET_OUT)/lib64
LOCAL_MODULE_PATH_32 := $(TARGET_OUT)/lib
LOCAL_MULTILIB := both

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..
LOCAL_CPP_INCLUDES := $(LOCAL_PATH)/..


LOCAL_SRC_FILES := \
    CHJCarDiagReader.cpp \
    CHJCarDiagCommThread.cpp \
    CHJCarDiagDTCMonitor.cpp \
    CHJCarDiagDTCThread.cpp \
    CHJCarDiagDTCHal.cpp \
    CHJCarDiagVehicleInfo.cpp

LOCAL_SHARED_LIBRARIES := \
    libandroid_runtime \
    libnativehelper \
    libcutils \
    libutils \
    liblog \
    libhardware \
    libhwbinder \
    libhidltransport \
    libhidlbase \
    libbinder \
    android.hardware.fcdiagnose@1.0 \
    android.hardware.automotive.vehicle@2.0 
    
       

LOCAL_STATIC_LIBRARIES := libjsoncpp

LOCAL_CPP_EXTENSION := .cpp

LOCAL_CPPFLAGS := -Wformat -Wunused-parameter 

LOCAL_MODULE := libchjcar_diag_native

include $(BUILD_SHARED_LIBRARY)

