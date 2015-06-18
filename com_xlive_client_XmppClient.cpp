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

#include "talk/base/thread.h"
#include "talk/base/asyncudpsocket.h"
#include "mcast_common.h"
//#define LOG_NDEBUG 0
#include <utils/Log.h>
#include "json/value.h"
#include "json/writer.h"

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

JNIEXPORT void JNICALL Java_com_xlive_client_XmppClient_send_1xmpp_1info(
        JNIEnv *env, jclass clazz, jstring server, jstring username,
        jstring password, jint port, jboolean tlsEnabled)
{
    const char *ip = "226.0.0.1";
    const int mcast_port = 4096;
    const char* native_username = env->GetStringUTFChars(username, JNI_FALSE);
    const char* native_password = env->GetStringUTFChars(password, JNI_FALSE);
    const char* native_server = env->GetStringUTFChars(server, JNI_FALSE);
    const int native_port = static_cast<int>(port);
    const bool native_tls_enabled = static_cast<bool>(tlsEnabled);
    LOGFL("Java_com_xlive_client_XmppClient_send_1xmpp_1info "
            "server: %s port: %d username: %s tls_enable: %d to multicast addr: %s",
            native_server, native_port, native_username, native_tls_enabled, ip);

    Json::Value root;
    root["updateAccount"] = true;
    root["username"] = native_username;
    root["password"] = native_password;
    root["server"] = native_server;
    root["port"] = native_port;
    root["tls_enabled"] = native_tls_enabled;

    Json::StyledWriter writer;
    std::string jstr = writer.write(root);

    int mcast_fd = create_mcast_client_socket();
    talk_base::AsyncSocket* sock = talk_base::Thread::Current()->socketserver()->WrapSocket(mcast_fd);
    talk_base::AsyncUDPSocket udpSocket(sock);
    udpSocket.SendTo(jstr.c_str(), jstr.size(), talk_base::SocketAddress(ip, mcast_port));
    close(mcast_fd);

    env->ReleaseStringUTFChars(username, native_username);
    env->ReleaseStringUTFChars(password, native_password);
    env->ReleaseStringUTFChars(server, native_server);
}

