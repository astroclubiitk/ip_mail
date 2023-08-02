#include <ip_mail/network.h>

Network::Network(){
  this->connect_socket();
  this->inet();
}

void Network::connect_socket(){
  this->sock = socket(PF_INET, SOCK_DGRAM, 0);
  
  if (sock == -1){
    std::cerr << "Could not connect to socket!" << std::endl;
    exit(1);
  }

  std::memset(&this->loopback, 0, sizeof(this->loopback));
  this->loopback.sin_family = AF_INET;
  this->loopback.sin_addr.s_addr = 1337;
  this->loopback.sin_port = htons(9);

  if (connect(this->sock, reinterpret_cast<sockaddr*>(&this->loopback), sizeof(this->loopback)) == -1){
    close(this->sock);
    std::cerr << "Could not connect!" << std::endl;
    exit(1);
  }

  this->addr_len = sizeof(loopback);
  if (getsockname(this->sock, reinterpret_cast<sockaddr*>(&loopback), &this->addr_len) == -1){
    close(this->sock);
    std::cerr << "Could not get socket name!" << std::endl;
    exit(1);
  }

  close(this->sock);
}

void Network::inet(){
  char* buffer = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
  if (inet_ntop(AF_INET, &this->loopback.sin_addr, buffer, INET_ADDRSTRLEN) == 0x0){
    std::cerr << "Could not inet ntop!" << std::endl;
    exit(1);
  }

  this->ip = buffer;
}

std::string Network::get_ip(){
  std::string ip_addr = this->ip;
  return ip_addr;
}