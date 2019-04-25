#Copyright (c) 2012-2018
#All Rights Reserved by Thunder Software Technology Co., Ltd and its affiliates.
#You may not use, copy, distribute, modify, transmit in any form this file
#except in compliance with THUNDERSOFT in writing by applicable law.

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ROOT_DIR := ../../../../../../../

LOCAL_MODULE := powertestservice

LOCAL_SRC_FILES := \
    src/main.cpp

LOCAL_CFLAGS += \
    -Wall \
    -Wextra \
    -Werror \
    -Wno-unused-parameter

LOCAL_C_INCLUDES += \
    $(ROOT_DIR)frameworks/base/include

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libcarpowermanager \
    liblog \
    libutils

LOCAL_MODULE_CLASS := EXECUTABLES

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
