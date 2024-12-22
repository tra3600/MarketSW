#ifndef SMTP_CLIENT_H
#define SMTP_CLIENT_H

#include <string>

class SmtpClient {
public:
    SmtpClient(const std::string& server, int port, const std::string& username, const std::string& password);
    void sendEmail(const std::string& to, const std::string& subject, const std::string& body);

private:
    std::string server;
    int port;
    std::string username;
    std::string password;
};

#endif // SMTP_CLIENT_H