LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(M64P_API_INCLUDES)
MY_LOCAL_SHARED_LIBRARIES := libhidapi

LOCAL_SRC_FILES := plugin.c

LOCAL_MODULE := mupen64plus-input-raphnet
LOCAL_CFLAGS := $(COMMON_CFLAGS)
LOCAL_LDFLAGS := $(COMMON_LDFLAGS)
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
