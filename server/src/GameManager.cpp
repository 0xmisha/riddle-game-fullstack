#include "../include/GameManager.h"

GameManager::GameManager(const std::string &directoryPath, unsigned seed)
    : seed(seed) {
  riddles = parseRiddlesFromDirectory(directoryPath);
  if (riddles.empty()) {
    std::cerr << "No riddles found in the directory." << std::endl;
  }
}

void GameManager::chooseRiddle() {
  if (riddles.empty()) {
    std::cerr << "Riddles list is empty." << std::endl;
    return;
  }
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<size_t> distribution(0, riddles.size() - 1);
  size_t randomIndex = distribution(generator);

  currentRiddle = &riddles[randomIndex];
  attemptsLeft = currentRiddle->getAttemptsAmount();
}

bool GameManager::checkGuess(const std::string &guess) {
  if (!currentRiddle) {
    std::cerr << "No riddle has been chosen yet." << std::endl;
    return false;
  }
  attemptsLeft--;
  return guess == currentRiddle->getWord();
}

std::string GameManager::getHint() {
  if (!currentRiddle) {
    return "No riddle chosen.";
  }
  if (hintsLeft != 0) {
    if (hintsLeft == 2) {
      hintsLeft--;
      return currentRiddle->getHint1();
    } else if (hintsLeft == 1) {
      hintsLeft--;
      return currentRiddle->getHint2();
    }
  }
  return "No hints left";
}

int GameManager::getAttemptsLeft() const {
  if (!currentRiddle) {
    return 0;
  }
  if (attemptsLeft <= 0) {
    return 0;
  }
  return attemptsLeft;
}

std::string GameManager::getWord() const {
  if (!currentRiddle) {
    return 0;
  }
  return currentRiddle->getWord();
}

std::string GameManager::getCurrentRiddleDescription() const {
  if (!currentRiddle) {
    return "No riddle chosen.";
  }
  return currentRiddle->getDescription();
}