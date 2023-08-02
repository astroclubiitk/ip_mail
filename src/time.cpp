#include <ip_mail/time.h>

Time::Time(){
  time_t time_now = time(nullptr);
  tm* local_time = localtime(&time_now);
  
  this->current = asctime(local_time);
  this->current = this->current.substr(0, this->current.size()-1);
}

std::string Time::now(){
  return this->current;
}