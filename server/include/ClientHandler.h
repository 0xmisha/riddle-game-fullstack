#ifndef RIDDLE_SERVER_INCLUDE_CLIENTHANDLER_H_
#define RIDDLE_SERVER_INCLUDE_CLIENTHANDLER_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <set>
#include <mutex>

#include "Parser.h"
#include "GameManager.h"
#include "ServerNetworkHandler.h"

static std::set<std::string> connectedClients;
static std::mutex clientsMutex;

class ClientHandler {
 public:
  ClientHandler(const std::string& pathToRiddles, unsigned int seed) : gameManager(pathToRiddles, seed) {}
  void operator()(int clientSocket);

 private:
  GameManager gameManager;
  std::string clientName;

  bool processMessage(const std::string& messageStr, int clientSocket);
};

#endif // RIDDLE_SERVER_INCLUDE_CLIENTHANDLER_H_
