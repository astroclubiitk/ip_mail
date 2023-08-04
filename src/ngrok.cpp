#include <ip_mail/ngrok.h>

Ngrok::Ngrok(){
  this->curl = curl_easy_init();

  this->setup();
  this->find_endpoint();
}

std::string Ngrok::get_endpoint(){
  return this->endpoint;
}

void Ngrok::setup(){
  if (!this->curl){
    std::cerr << "[ERROR]: CURL not found!" << std::endl;
    exit(1);
  }

  curl_easy_setopt(this->curl, CURLOPT_URL, this->curl_url.c_str());
  curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, write);
}

void Ngrok::find_endpoint(){
  std::string response_data;
  curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &response_data);
  
  int i = SLEEP_TIMEOUT;
  while ((i--) && (res != CURLE_OK)){
    response_data.clear();
    this->res = curl_easy_perform(this->curl);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  if (res != CURLE_OK){
    std::cerr << "[ERROR] Curl easy perform failed! " << curl_easy_strerror(res) << std::endl;
    exit(1);
  }

  this->endpoint = this->find_value_by_key(response_data, "public_url");
  this->finish();
}

size_t Ngrok::write(void* contents, size_t size, size_t nmemb, std::string* output){
  size_t total_size = size * nmemb;
  if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)){
    return 0;
  }
  output->append((char*)contents, total_size);
  return total_size;
}

std::string Ngrok::find_value_by_key(std::string& json_str, const std::string& key){
  size_t key_pos = json_str.find("\"" + key + "\"");
  if (key_pos == std::string::npos){
    return "";
  }

  size_t value_pos = json_str.find("\"", key_pos + key.length() + 3);
  size_t end_pos = json_str.find("\"", value_pos + 1);
  return json_str.substr(value_pos+1, end_pos-value_pos-1);
}

void Ngrok::finish(){
  curl_easy_cleanup(this->curl);
}