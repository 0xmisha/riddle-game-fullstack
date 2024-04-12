#ifndef RIDDLE_CLIENT_INCLUDE_CLIENTNETWORKHANDLER_H_
#define RIDDLE_CLIENT_INCLUDE_CLIENTNETWORKHANDLER_H_

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class ClientNetworkHandler {
 private:
  int sock;
  sockaddr_in serverAddress;
  bool isValidIpAddress(const std::string& ip);
 public:
  ClientNetworkHandler(const std::string& ip, int port);
  ~ClientNetworkHandler();
  void sendMessage(const std::string& message);
  std::string receiveMessage();
};


#endif //RIDDLE_CLIENT_INCLUDE_CLIENTNETWORKHANDLER_H_
