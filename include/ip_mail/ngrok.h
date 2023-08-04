#include <thread>
#include <iostream>
#include <curl/curl.h>

#include <ip_mail/config.h>

class Ngrok
{
  private:
    std::string curl_url = "http://localhost:4040/api/tunnels";
    std::string endpoint;

    CURL* curl;
    CURLcode res;

    void setup();
    void find_endpoint();
    static size_t write(void* contents, size_t size, size_t nmemb, std::string* output);
    std::string find_value_by_key(std::string& json_str, const std::string& key);
    void finish();

  public:
    Ngrok();

    std::string get_endpoint();
};