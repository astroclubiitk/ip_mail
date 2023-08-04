#include <ip_mail/email.h>

static const char* email_payload_text;

Email::Email(){
  this->res = CURLE_OK;
  this->recipients = NULL;
  this->upload_ctx = { 0 };
  this->curl = curl_easy_init();
}

void Email::configure(const std::string username, const std::string password){
  this->username = username;
  this->password = password;

  this->setup();
}

void Email::setup(){
  if (!curl){
    std::cerr << "[ERROR]: CURL not found!" << std::endl;
    exit(1);
  }

  this->payload_text = "To: Observatory " + this->username +
    "\r\nFrom: Observatory " + this->username +
    "\r\nSubject: [UPDATE] IP Address\r\n\r\n";

  curl_easy_setopt(this->curl, CURLOPT_USERNAME, this->username.c_str());
  curl_easy_setopt(this->curl, CURLOPT_PASSWORD, this->password.c_str());
  curl_easy_setopt(this->curl, CURLOPT_URL, "smtp://smtp.gmail.com");
  curl_easy_setopt(this->curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
  curl_easy_setopt(this->curl, CURLOPT_PORT, 587);
  curl_easy_setopt(this->curl, CURLOPT_MAIL_FROM, this->username.c_str());
  curl_easy_setopt(this->curl, CURLOPT_READFUNCTION, payload_source);
  curl_easy_setopt(this->curl, CURLOPT_READDATA, &this->upload_ctx);
  curl_easy_setopt(this->curl, CURLOPT_UPLOAD, 1L);
  // curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
  
}

size_t Email::payload_source(char* ptr, size_t size, size_t nmemb, void* userp){
  struct upload_status* upload_ctx = (struct upload_status*) userp;
  const char* data;
  size_t room = size * nmemb;
  
  if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)){
    return 0;
  }

  data = &email_payload_text[upload_ctx->bytes_read];
  if (data){
    size_t len = strlen(data);
    if (room < len)
      len = room;
    memcpy(ptr, data, len);
    upload_ctx->bytes_read += len;

    return len;
  }

  return 0;
}

void Email::send(std::string dest_email, std::string ip_addr, std::string endpoint, std::string time){
  if ((this->username.empty()) || (this->password.empty())){
    std::cerr << "[ERROR] class Email not configured. Use Email.configure() first!" << std::endl;
    exit(1);
  }

  std::string message = "Dear Coordinators,\r\n\r\nThis email is generated to inform you that there was a power supply interruption at observatory causing the system to restart at " + time + ".\r\n\r\nThe new IP address of the system is: " + ip_addr + "\r\n" + "Ngrok tunneling to: " + endpoint + "\r\n\r\nRegards,\r\n\r\nObservatory RaspberryPi\r\n";
  this->payload_text = this->payload_text + message;
  email_payload_text = this->payload_text.c_str();

  this->recipients = curl_slist_append(this->recipients, dest_email.c_str());
  curl_easy_setopt(this->curl, CURLOPT_MAIL_RCPT, this->recipients); 

  this->res = curl_easy_perform(this->curl);
  if (res != CURLE_OK){
    std::cerr << "[ERROR] Curl easy perform failed! " << curl_easy_strerror(res) << std::endl;
  }
  
  this->finish();
}

void Email::finish(){
  curl_slist_free_all(this->recipients);
  curl_easy_cleanup(this->curl);
}