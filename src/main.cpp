#include <ip_mail/network.h>
#include <ip_mail/time.h>
#include <ip_mail/email.h>
#include <ip_mail/ngrok.h>

int main(int argc, char** argv){
  Network network;
  std::string ip_addr = network.get_ip();

  Time current_time;
  std::string now = current_time.now();

  Ngrok ngrok;
  std::string endpoint = ngrok.get_endpoint();
  
  Email email;
	email.configure(EMAIL_ID, EMAIL_PASSWORD);
	email.send(DEST_EMAIL, ip_addr, endpoint, now);

  return 0;
}