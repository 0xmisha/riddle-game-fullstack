/**
 * @file MainClient.h
 * @brief Manages the main client operations in the riddle game.
 *
 * This class handles interactions with the server through the ClientNetworkHandler and
 * interfaces with the user through the UserInterface class. It manages the game logic
 * from the client side, responding to user inputs and server responses.
 */

#ifndef RIDDLE_CLIENT_INCLUDE_MAINCLIENT_H_
#define RIDDLE_CLIENT_INCLUDE_MAINCLIENT_H_

#include "ClientNetworkHandler.h"
#include "UserInterface.h"
#include "Parser.h"
#include <unordered_map>
#include <string>

class MainClient {
 private:
  ClientNetworkHandler networkHandler; ///< Handles network communication.
  std::string riddle; ///< Current riddle description.

 public:
  /**
   * @brief Constructs a MainClient connected to the specified server IP and port.
   * @param ip IP address of the server.
   * @param port Port number on the server.
   */
  MainClient(const std::string& ip, int port);

  /**
   * @brief Starts the game by requesting a riddle from the server.
   */
  void startGame();

  /**
   * @brief Submits a guess to the server and handles the response.
   * @param word The user's guess for the current riddle.
   */
  void makeGuess(const std::string& word);

  /**
   * @brief Requests a hint from the server for the current riddle.
   */
  void requestHint();

  /**
   * @brief Surrenders the current riddle, requesting the answer from the server.
   */
  void surrender();
};

#endif // RIDDLE_CLIENT_INCLUDE_MAINCLIENT_H_
