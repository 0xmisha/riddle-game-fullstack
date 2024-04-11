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
  std::string word;
  std::string description;
  std::string hint1;
  std::string hint2;
  int attempts_amount;

 public:
  Riddle(std::string word, std::string description)
      : word(std::move(word)), description(std::move(description)), attempts_amount(0) {}

  const std::string& getWord() const { return word; }
  const std::string& getDescription() const { return description; }
  const std::string& getHint1() const { return hint1; }
  const std::string& getHint2() const { return hint2; }
  int getAttemptsAmount() const { return attempts_amount; }
  void setHint1(const std::string& hint) { hint1 = hint; }
  void setHint2(const std::string& hint) { hint2 = hint; }
  void setTriesAmount(int amount) { attempts_amount = amount; }

};

Riddle parseRiddleFromFile(const std::string& filePath);

std::vector<Riddle> parseRiddlesFromDirectory(const std::string& directoryPath);

#endif //RIDDLE_SERVER_INCLUDE_RIDDLE_H_
