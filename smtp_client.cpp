#include "smtp_client.h"
#include <curl/curl.h>

SmtpClient::SmtpClient(const std::string& server, int port, const std::string& username, const std::string& password)
    : server(server), port(port), username(username), password(password) {}

void SmtpClient::sendEmail(const std::string& to, const std::string& subject, const std::string& body) {
    CURL* curl;
    CURLcode res = CURLE_OK;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, server.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, ("<" + username + ">").c_str());

        struct curl_slist* recipients = NULL;
        recipients = curl_slist_append(recipients, to.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        std::string data = "To: " + to + "\r\n" +
                           "From: " + username + "\r\n" +
                           "Subject: " + subject + "\r\n" +
                           "\r\n" + body;

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}