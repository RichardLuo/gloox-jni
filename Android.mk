##################################################################
# author: Raymond Wen
# date:   2015-06-12
#                                                                
##################################################################

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
#include $(LOCAL_PATH)/../common.mk
#include $(LOCAL_PATH)/../jingle/jingle_common.mk

LOCAL_MODULE := libxmpp_registration_jni

LOCAL_SRC_FILES := \
	com_xlive_client_XmppClient.cpp \
	Register.cpp

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../gloox/src \
	$(LOCAL_PATH)/../

LOCAL_LDLIBS := -llog

LOCAL_SHARED_LIBRARIES := \
	libgloox

include $(BUILD_SHARED_LIBRARY)
