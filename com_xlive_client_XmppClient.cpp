/*
 * Copyright (C) 2013 The X-Live Project
 *
 * @author Raymond Wen
 * 
 * @date   2015-06-12
 * 
 ****************************************************************** 
 */

#define LOG_TAG "XmppClient_jni"

#include "com_xlive_client_XmppClient.h"
#include "Register.h"

//#define LOG_NDEBUG 0
#include <utils/Log.h>

JNIEXPORT jint JNICALL Java_com_xlive_client_XmppClient_register_1user(
    JNIEnv *env, jclass clazz, jstring server_url, jstring user_name, jstring password)
{
    const char* native_server = env->GetStringUTFChars(server_url, JNI_FALSE);
    std::string server(native_server);
    Register *r = new Register(server);
    const char* native_user_name = env->GetStringUTFChars(user_name, JNI_FALSE);
    const char* native_password = env->GetStringUTFChars(password, JNI_FALSE);
    LOGFL("Java_com_xlive_client_XmppClient_register_user %s to server %s",
            native_user_name, native_server);
    int result = r->addAccount(native_user_name, native_password);
    
    env->ReleaseStringUTFChars(user_name, native_user_name);
    env->ReleaseStringUTFChars(password, native_password);
    env->ReleaseStringUTFChars(server_url, native_server);

    LOGFL("Java_com_xlive_client_XmppClient_register_user");
    return result;
}
