/**
 * @file GameManager.h
 * @brief Manages the game logic for the riddle game server.
 *
 * This class handles operations such as selecting riddles, checking guesses,
 * providing hints, and tracking the number of remaining attempts for a given riddle.
 */

#ifndef RIDDLE_SERVER_INCLUDE_GAMEMANAGER_H_
#define RIDDLE_SERVER_INCLUDE_GAMEMANAGER_H_

#include <vector>
#include <random>
#include <chrono>
#include "Riddle.h"

class GameManager {
 private:
  std::vector<Riddle> riddles; ///< List of all available riddles.
  Riddle* currentRiddle; ///< Pointer to the current active riddle.
  unsigned seed; ///< Seed for random number generation.
  int attemptsLeft; ///< Number of attempts left for the current riddle.
  int hintsLeft; ///< Number of hints left for the current riddle.

 public:
  /**
   * @brief Constructs a game manager with riddles loaded from a specified directory.
   * @param directoryPath Path to the directory containing riddle files.
   * @param seed Seed used for random number generation to ensure different game play on restart.
   */
  GameManager(const std::string& directoryPath, unsigned seed);

  /**
   * @brief Randomly selects a riddle for the player to solve.
   */
  void chooseRiddle();

  /**
   * @brief Checks if the player's guess matches the current riddle's answer.
   * @param guess The player's guess.
   * @return True if the guess is correct, false otherwise.
   */
  bool checkGuess(const std::string& guess);

  /**
   * @brief Gets the description of the current riddle.
   * @return The description of the current riddle.
   */
  std::string getCurrentRiddleDescription() const;

  /**
   * @brief Provides a hint for the current riddle.
   * @return A hint to help solve the riddle.
   */
  std::string getHint();

  /**
   * @brief Returns the number of attempts left for the current riddle.
   * @return The number of attempts left.
   */
  int getAttemptsLeft() const;

  /**
   * @brief Retrieves the answer to the current riddle.
   * @return The correct word for the current riddle.
   */
  std::string getWord() const;
};

#endif // RIDDLE_SERVER_INCLUDE_GAMEMANAGER_H_
