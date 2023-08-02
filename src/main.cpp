#include <ip_mail/config.h>
#include <ip_mail/network.h>
#include <ip_mail/time.h>
#include <ip_mail/email.h>

int main(int argc, char** argv){
  Network network;
  std::string ip_addr = network.get_ip();

  Time current_time;
  std::string now = current_time.now();

  Email email;
	email.configure(EMAIL_ID, EMAIL_PASSWORD);
	email.send(ip_addr, now);

  return 0;
}