#ifndef RIDDLE_SERVER_INCLUDE_SERVERNETWORKHANDLER_H_
#define RIDDLE_SERVER_INCLUDE_SERVERNETWORKHANDLER_H_

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

#define BUF_SIZE 4096

class ServerNetworkHandler {
 public:
  static bool sendResponse(int clientSocket, const std::string& response) {
    ssize_t bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
    if (bytesSent < 0) {
      std::cerr << "Failed to send response to client." << std::endl;
      return false;
    }
    return true;
  }

  static std::string receiveRequest(int clientSocket) {
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    ssize_t bytesReceived = read(clientSocket, buffer, sizeof(buffer) - 1);
    if (bytesReceived <= 0) {
      std::cerr << "Failed to read request from client or client disconnected." << std::endl;
      return "";
    }
    return std::string(buffer, bytesReceived);
  }
};

#endif // RIDDLE_SERVER_INCLUDE_SERVERNETWORKHANDLER_H_
