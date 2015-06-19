/*
 *  Copyright (c) 2004-2015 by Jakob Schröter <js@camaya.net>
 *  This file is part of the gloox library. http://camaya.net/gloox
 *
 *  This software is distributed under a license. The full license
 *  agreement can be found in the file LICENSE in this distribution.
 *  This software may not be copied, modified, sold or distributed
 *  other than expressed in the named license agreement.
 *
 *  This software is distributed without any warranty.
 */

#include "Register.h"
using namespace gloox;

#include <pthread.h>
#include <stdio.h>
#include <locale.h>
#include <string>

#include <cstdio> // [s]print[f]

int Register::addAccount(const std::string& username, const std::string& password)
{
    j = new Client(m_server);
    LOGFL("addAccount username: %s, password: %s", username.c_str(), password.c_str());
    m_user_name = username;
    m_password = password;
    j->disableRoster();
    j->registerConnectionListener(this);

    m_reg = new Registration(j);
    m_reg->registerRegistrationHandler(this);

    j->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, this);

    j->connect();

    delete(m_reg);
    delete(j);
    return m_result;
}

void Register::onConnect()
{
    LOGFL("onConnect, about to fectchRegistrationFields");
    m_reg->fetchRegistrationFields();
}

void Register::onDisconnect(ConnectionError e)
{
    LOGFL("register_test: disconnected\n");
}

bool Register::onTLSConnect(const CertInfo& info)
{
    LOGFL("status: %d\nissuer: %s\npeer: %s\nprotocol: %s\nmac: %s\ncipher: %s\ncompression: %s\n",
          info.status, info.issuer.c_str(), info.server.c_str(),
          info.protocol.c_str(), info.mac.c_str(), info.cipher.c_str(),
          info.compression.c_str());
    return true;
}

void Register::handleRegistrationFields(const JID& from, int fields, std::string instructions)
{
    RegistrationFields vals;
    vals.username = m_user_name;
    vals.password = m_password;
    m_reg->createAccount(fields, vals);
}

void Register::handleRegistrationResult(const JID& /*from*/, RegistrationResult result)
{
    m_result = result;
    if(gloox::RegistrationSuccess != m_result)
    {
        LOGFL("result: %d is not RegistrationSuccess\n", m_result);
    }
    else
    {
        LOGFL("result: %d is RegistrationSuccess, registration ok\n", m_result);
    }
    j->disconnect();
}

void Register::handleAlreadyRegistered(const JID& /*from*/)
{
    LOGFL("the account already exists.\n");
}

void Register::handleDataForm(const JID& /*from*/, const DataForm& /*form*/)
{
    LOGFL("datForm received\n");
}

void Register::handleOOB(const JID& /*from*/, const OOB& oob)
{
    LOGFL("OOB registration requested. %s: %s\n", oob.desc().c_str(), oob.url().c_str());
}

void Register::handleLog(LogLevel level, LogArea area, const std::string& message)
{
    LOGFL("log: level: %d, area: %d, %s\n", level, area, message.c_str());
}
