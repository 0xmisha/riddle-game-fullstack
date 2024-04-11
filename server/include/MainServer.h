#ifndef RIDDLE_SERVER_INCLUDE_MAINSERVER_H_
#define RIDDLE_SERVER_INCLUDE_MAINSERVER_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "ClientHandler.h"

class MainServer {
 private:
  int serverSocket;
  struct sockaddr_in serverAddress;
  const int port;
  const std::string& pathToRiddles;
  unsigned int seed;

 public:
  explicit MainServer(int port = 8080, const std::string& pathToRiddles = "../riddles", unsigned int seed = 1);
  void acceptConnections();
  ~MainServer() { close(serverSocket); }
};

#endif //RIDDLE_SERVER_INCLUDE_MAINSERVER_H_
