#ifndef REGISTER_H_
#define REGISTER_H_

#include "utils/Log.h"
#include "client.h"
#include "connectionlistener.h"
#include "registration.h"
#include "logsink.h"
#include "loghandler.h"

class Register : public gloox::RegistrationHandler, gloox::ConnectionListener, gloox::LogHandler
{
  public:
    Register(std::string& server) : m_server(server) {}
    virtual ~Register() {}

    void start();
    int addAccount(const std::string& username, const std::string& password);
    // ConnectionListener
    virtual void onConnect();
    // ConnectionListener
    virtual void onDisconnect(gloox::ConnectionError);
    // ConnectionListener
    virtual bool onTLSConnect(const gloox::CertInfo&);
    // RegistrationHandler
    virtual void handleRegistrationFields(const gloox::JID& /*from*/, int fields, std::string instructions);
    // RegistrationHandler
    virtual void handleRegistrationResult(const gloox::JID& /*from*/, gloox::RegistrationResult result);
    // RegistrationHandler
    virtual void handleAlreadyRegistered(const gloox::JID& /*from*/ );
    // RegistrationHandler
    virtual void handleDataForm(const gloox::JID& /*from*/, const gloox::DataForm& /*form*/);
    virtual void handleOOB(const gloox::JID& /*from*/, const gloox::OOB& oob);
    // LogHandler
    virtual void handleLog(gloox::LogLevel level, gloox::LogArea area, const std::string& message);

  private:
    gloox::Registration *m_reg;
    gloox::Client *j;
    std::string m_server;
    std::string m_user_name;
    std::string m_password;
    int m_result;
};

#endif /* end of include guard: REGISTER_H_ */
