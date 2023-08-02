#include <iostream>
#include <string>
#include <string.h>
#include <curl/curl.h>

struct upload_status {
  size_t bytes_read;
};

class Email
{
  private:
    std::string username;
    std::string password;
    std::string payload_text;

    CURL* curl;
    CURLcode res;
    struct curl_slist* recipients;
    struct upload_status upload_ctx;
    
    void setup();
    void finish();
    static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp);

  public:
    Email();

    void configure(const std::string username, const std::string password);
    void send(std::string dest_email, std::string ip_addr, std::string time);
};