/**
 * @file ClientHandler.h
 * @brief Handles individual client connections for the riddle game server.
 *
 * This class is responsible for managing the communication with a connected client,
 * processing their messages, and coordinating responses based on game logic.
 */

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

/**
 * @brief Tracks connected clients using their names.
 */
static std::set<std::string> connectedClients;

/**
 * @brief Provides thread-safe access to the connectedClients set.
 */
static std::mutex clientsMutex;

class ClientHandler {
 public:
  /**
   * @brief Constructs a ClientHandler with specific game settings.
   * @param pathToRiddles Path to the directory containing riddle files.
   * @param seed Seed for random number generation in game logic.
   */
  ClientHandler(const std::string& pathToRiddles, unsigned int seed);

  /**
   * @brief Handles the client-server communication for a single client.
   * @param clientSocket The socket descriptor for the client connection.
   * This function is designed to run in a separate thread for each client.
   */
  void operator()(int clientSocket);

 private:
  GameManager gameManager; ///< Manages the game logic.
  std::string clientName; ///< Stores the name of the client for session management.

  /**
   * @brief Processes a single message received from the client.
   * @param messageStr The message string received from the client.
   * @param clientSocket The socket descriptor for the client connection.
   * @return True if the message was processed successfully, False if the session should end.
   * This function decodes messages and interacts with the GameManager to produce appropriate responses.
   */
  bool processMessage(const std::string& messageStr, int clientSocket);
};

#endif // RIDDLE_SERVER_INCLUDE_CLIENTHANDLER_H_
