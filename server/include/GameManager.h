#ifndef RIDDLE_SERVER_INCLUDE_GAMEMANAGER_H_
#define RIDDLE_SERVER_INCLUDE_GAMEMANAGER_H_

#include <vector>
#include <random>
#include <chrono>
#include "Riddle.h"

class GameManager {
 private:
  std::vector<Riddle> riddles;
  Riddle *currentRiddle = nullptr;
  unsigned seed;
  int attemptsLeft;
  int hintsLeft = 2;

 public:
  GameManager(const std::string &directoryPath, unsigned seed);

  void chooseRiddle();

  bool checkGuess(const std::string &guess);

  std::string getCurrentRiddleDescription() const;

  std::string getHint();

  int getAttemptsLeft() const;

  std::string getWord() const;
};

#endif // RIDDLE_SERVER_INCLUDE_GAMEMANAGER_H_
