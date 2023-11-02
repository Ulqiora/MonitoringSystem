#pragma once
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include <curl/curl.h>
#include <string>
#include <filesystem>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>
//#include <Poco/Net/S
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/StringPartSource.h>
using Poco::Net::InvalidCertificateHandler;
using Poco::Net::AcceptCertificateHandler;
using Poco::Net::Context;
using Poco::Net::SSLManager;
using Poco::Net::SecureStreamSocket;
using Poco::Net::SocketAddress;
using Poco::Net::SecureSMTPClientSession;
using Poco::Net::SMTPClientSession;
using Poco::SharedPtr;
using Poco::Net::MailMessage;
using Poco::Net::MailRecipient;
using Poco::Net::StringPartSource;
using namespace std;


static size_t read_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    size_t totalSize = size * nmemb;
    ptr = static_cast<char*>(userdata);
    return totalSize;
}

namespace Email{
class EmailPrinter{
private:
    class SSLInitializer{
    public:
        SSLInitializer(){Poco::Net::initializeSSL();}
        ~SSLInitializer(){Poco::Net::uninitializeSSL();}
    };
    const std::string URL_ =  "smtp.gmail.com";
    SSLInitializer sslInitializer;
    SecureSMTPClientSession session;
    Context::Ptr pContext;
    const std::string userPassword = "glpw vgsz gguh cvli";
    const std::string userName = "monitoringsystem.school21@gmail.com";
    std::string userRecipient = "damdinov@jcraster.ru";
//    const std::string messageFile_= "message.txt";
//    const std::string folderName = "messages";

public:
    EmailPrinter():sslInitializer(),session(URL_){
//        SSLInitializer sslInitializer;
        SharedPtr<InvalidCertificateHandler> pCert = new AcceptCertificateHandler(false);
        pContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_RELAXED, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        SSLManager::instance().initializeClient(0, pCert, pContext);
        session.login();
        session.startTLS(pContext);
    }
    void sendMessage(std::string_view subject, std::string_view message_content){
        MailMessage message;
        message.setSender(userName);
        message.addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, userRecipient));
        message.setSubject(subject.data());
//        std::string content;
//        content += "Hello ";
//        content += userRecipient;
//        content += ",\r\n\r\n";
//        content += "This is a greeting from the POCO C++ Libraries.\r\n\r\n";
        message.addContent(new StringPartSource(message_content.data()));
        if (!userName.empty())
        {
            session.login(SMTPClientSession::AUTH_LOGIN, userName, userPassword);
        }
        session.sendMessage(message);
        session.close();
    }
    ~EmailPrinter(){session.close();}
};
}
//curl -v --url "smtps://smtp.gmail.com:465" --ssl-reqd --mail-from "damdinovandrey@gmail.com" --user "damdinovandrey@gmail.com" --mail-rcpt "damdinov@jcraster.ru" -u damdinovandrey@gmail.com:"odry kjkl uhdr dbep" -T CMakeLists.txt
