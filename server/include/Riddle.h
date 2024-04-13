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
  Riddle(std::string word, std::string description);

  /// Getters for riddle properties
  const std::string& getWord() const;
  const std::string& getDescription() const;
  const std::string& getHint1() const;
  const std::string& getHint2() const;
  int getAttemptsAmount() const;

  /// Setters for hints and attempts
  void setHint1(const std::string& hint);
  void setHint2(const std::string& hint);
  void setTriesAmount(int amount);
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
