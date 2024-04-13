/**
 * @file ServerNetworkHandler.h
 * @brief Provides static methods for server-client communication.
 *
 * This class includes methods to send responses to and receive requests from clients,
 * facilitating communication between the server and its connected clients.
 */

#ifndef RIDDLE_SERVER_INCLUDE_SERVERNETWORKHANDLER_H_
#define RIDDLE_SERVER_INCLUDE_SERVERNETWORKHANDLER_H_

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

#define BUF_SIZE 4096 ///< Buffer size for receiving data.

class ServerNetworkHandler {
 public:
  /**
   * @brief Sends a response to the client.
   * @param clientSocket The socket descriptor for the client.
   * @param response The message to send.
   * @return True if the message was sent successfully, false otherwise.
   */
  static bool sendResponse(int clientSocket, const std::string& response) {
    ssize_t bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
    if (bytesSent < 0) {
      std::cerr << "Failed to send response to client." << std::endl;
      return false;
    }
    return true;
  }

  /**
   * @brief Receives a request from the client.
   * @param clientSocket The socket descriptor for the client.
   * @return The received message as a string, or an empty string if an error occurred.
   */
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
