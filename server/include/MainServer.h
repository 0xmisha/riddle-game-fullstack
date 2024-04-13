/**
 * @file MainServer.h
 * @brief Manages the main server operations for the riddle game.
 *
 * This class is responsible for initializing the server, accepting client connections,
 * and managing active client sessions.
 */

#ifndef RIDDLE_SERVER_INCLUDE_MAINSERVER_H_
#define RIDDLE_SERVER_INCLUDE_MAINSERVER_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <set>
#include <mutex>

#include "ClientHandler.h"

class MainServer {
 private:
  int serverSocket; ///< Socket descriptor for the server.
  struct sockaddr_in serverAddress; ///< Structure containing the server address.
  const int port; ///< Port number on which the server listens.
  const std::string& pathToRiddles; ///< Path to the directory containing riddles.
  unsigned int seed; ///< Seed for generating random game behavior.
  std::set<std::string> connectedClientsNames; ///< Set of names of connected clients.
  std::mutex clientsMutex; ///< Mutex for thread-safe operations on connectedClientsNames.

 public:
  /**
   * @brief Constructor that initializes the server with specified settings.
   * @param port The port number for the server to listen on.
   * @param pathToRiddles Path to the directory containing riddle files.
   * @param seed Seed for random number generation.
   */
  explicit MainServer(int port, const std::string& pathToRiddles, unsigned int seed);

  /**
   * @brief Accepts new connections and handles them asynchronously.
   */
  void acceptConnections();

  /**
   * @brief Attempts to add a new client's name to the set of connected clients.
   * @param name The name of the client to add.
   * @return True if the name was added successfully, false if the name is already present.
   */
  bool addClientName(const std::string& name);

  /**
   * @brief Removes a client's name from the set of connected clients.
   * @param name The name of the client to remove.
   */
  void removeClientName(const std::string& name);

  /**
   * @brief Destructor that closes the server socket.
   */
  ~MainServer() { close(serverSocket); };
};

#endif // RIDDLE_SERVER_INCLUDE_MAINSERVER_H_
