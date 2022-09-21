LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -fPIC -std=c99
LOCAL_LDFLAGS += -fPIC 
LOCAL_LDLIBS := -llog

LOCAL_MODULE    := live_audio_dji 
LOCAL_SRC_FILES := live_audio_dji.c

include $(BUILD_SHARED_LIBRARY)
