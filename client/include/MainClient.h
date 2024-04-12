#ifndef RIDDLE_CLIENT_INCLUDE_MAINCLIENT_H_
#define RIDDLE_CLIENT_INCLUDE_MAINCLIENT_H_

#include "ClientNetworkHandler.h"
#include "UserInterface.h"
#include "Parser.h"
#include <unordered_map>
#include <string>

class MainClient {
 private:
  ClientNetworkHandler networkHandler;
  std::string riddle;
 public:
  MainClient(const std::string& ip, int port);
  void startGame();
  void makeGuess(const std::string& word);
  void requestHint();
  void surrender();
};

#endif // RIDDLE_CLIENT_INCLUDE_MAINCLIENT_H_
