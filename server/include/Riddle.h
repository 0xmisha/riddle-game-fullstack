/**
 * @file Riddle.h
 * @brief Defines the Riddle class and associated parsing functions.
 *
 * This file includes the definition of the Riddle class, which stores details about individual riddles,
 * and functions to parse riddles from files and directories.
 */

#ifndef RIDDLE_SERVER_INCLUDE_RIDDLE_H_
#define RIDDLE_SERVER_INCLUDE_RIDDLE_H_

#include <iostream>
#include <string>
#include <utility>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <sstream>

class Riddle {
 private:
  std::string word; ///< The answer to the riddle.
  std::string description; ///< The description or question of the riddle.
  std::string hint1; ///< The first hint.
  std::string hint2; ///< The second hint.
  int attempts_amount; ///< Number of attempts allowed for this riddle.

 public:
  /**
   * @brief Constructs a riddle with specified word and description.
   * @param word The answer to the riddle.
   * @param description The question or description of the riddle.
   */
  Riddle(std::string word, std::string description)
      : word(std::move(word)), description(std::move(description)), attempts_amount(0) {}

  /// Getters for riddle properties
  const std::string& getWord() const { return word; }
  const std::string& getDescription() const { return description; }
  const std::string& getHint1() const { return hint1; }
  const std::string& getHint2() const { return hint2; }
  int getAttemptsAmount() const { return attempts_amount; }

  /// Setters for hints and attempts
  void setHint1(const std::string& hint) { hint1 = hint; }
  void setHint2(const std::string& hint) { hint2 = hint; }
  void setTriesAmount(int amount) { attempts_amount = amount; }
};

/**
 * @brief Parses a single riddle from a file.
 * @param filePath Path to the riddle file.
 * @return A Riddle object populated with data from the file.
 */
Riddle parseRiddleFromFile(const std::string& filePath);

/**
 * @brief Parses all riddles from a directory.
 * @param directoryPath Path to the directory containing riddle files.
 * @return A vector of Riddle objects.
 */
std::vector<Riddle> parseRiddlesFromDirectory(const std::string& directoryPath);

#endif // RIDDLE_SERVER_INCLUDE_RIDDLE_H_
