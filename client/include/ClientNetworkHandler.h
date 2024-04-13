/**
 * @file ClientNetworkHandler.h
 * @brief Handles network communication between client and server.
 *
 * This class is responsible for setting up and managing the network connection,
 * sending messages to, and receiving messages from the server.
 */

#ifndef RIDDLE_CLIENT_INCLUDE_CLIENTNETWORKHANDLER_H_
#define RIDDLE_CLIENT_INCLUDE_CLIENTNETWORKHANDLER_H_

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class ClientNetworkHandler {
 private:
  int sock;  ///< Socket descriptor for the client.
  sockaddr_in serverAddress; ///< Structure containing the server address.

  /**
   * @brief Validates the given IP address.
   * @param ip The IP address as a string.
   * @return True if the IP address is valid, false otherwise.
   */
  bool isValidIpAddress(const std::string& ip);

 public:
  /**
   * @brief Constructor that initializes a new ClientNetworkHandler.
   * @param ip The IP address of the server.
   * @param port The port number on which to connect to the server.
   */
  ClientNetworkHandler(const std::string& ip, int port);

  /**
   * @brief Destructor that closes the socket connection.
   */
  ~ClientNetworkHandler();

  /**
   * @brief Sends a message to the server.
   * @param message The message to be sent.
   */
  void sendMessage(const std::string& message);

  /**
   * @brief Receives a message from the server.
   * @return The received message as a string.
   */
  std::string receiveMessage();
};


#endif //RIDDLE_CLIENT_INCLUDE_CLIENTNETWORKHANDLER_H_
