#include <iostream>
#include <cstring>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Network
{
  private:
    int sock;
    char* ip;

    sockaddr_in loopback;
    socklen_t addr_len;

    void connect_socket();
    void inet();

  public:
    Network();

    std::string get_ip();
};