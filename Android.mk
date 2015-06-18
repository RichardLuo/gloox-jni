##################################################################
# author: Raymond Wen
# date:   2015-06-12
#                                                                
##################################################################

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
#include $(LOCAL_PATH)/../common.mk
include $(LOCAL_PATH)/../jingle/jingle_common.mk

LOCAL_MODULE := libxmpp_registration_jni

LOCAL_SRC_FILES := \
	com_xlive_client_XmppClient.cpp \
	Register.cpp

LOCAL_CFLAGS := \
	$(JINGLE_CFLAGS)

LOCAL_C_INCLUDES += \
	$(path_third_party)/jsoncpp/source/include \
	$(LOCAL_PATH)/../gloox/src \
	$(LOCAL_PATH)/../discovery \
	$(path_jingle) \
	$(LOCAL_PATH)/../

LOCAL_LDLIBS := -llog

LOCAL_SHARED_LIBRARIES := \
	libjsoncpp \
	libjingle \
	libgloox

include $(BUILD_SHARED_LIBRARY)
