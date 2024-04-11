#include "../include/Riddle.h"

Riddle parseRiddleFromFile(const std::string& filePath) {
  std::ifstream file(filePath);
  std::string word, description, hint1, hint2, line;
  int tries_amount;

  std::getline(file, word);
  std::getline(file, description);
  std::getline(file, hint1);
  std::getline(file, hint2);
  std::getline(file, line);
  std::istringstream(line) >> tries_amount;

  Riddle riddle(word, description);
  riddle.setHint1(hint1);
  riddle.setHint2(hint2);
  riddle.setTriesAmount(tries_amount);

  return riddle;
}

std::vector<Riddle> parseRiddlesFromDirectory(const std::string& directoryPath) {
  std::vector<Riddle> riddles;
  DIR* dir = opendir(directoryPath.c_str());
  struct dirent* entry;

  if (dir == nullptr) return riddles;

  while ((entry = readdir(dir)) != nullptr) {
    std::string fileName = entry->d_name;
    if (fileName.size() > 4 && fileName.substr(fileName.size() - 4) == ".rdl") {
      riddles.push_back(parseRiddleFromFile(directoryPath + "/" + fileName));
    }
  }

  closedir(dir);
  return riddles;
}