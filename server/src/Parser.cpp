#include "../include/Parser.h"

std::unordered_map<std::string, std::string> parseMessage(const std::string& input) {
  if (input.back() != '.') {
    throw std::invalid_argument("Input string does not end with a period.");
  }

  std::unordered_map<std::string, std::string> keyValuePairs;
  size_t start = 0;
  size_t end = 0;

  while ((end = input.find(',', start)) != std::string::npos) {
    auto pair = input.substr(start, end - start);
    auto delimiterPos = pair.find(':');
    if (delimiterPos != std::string::npos) {
      auto key = pair.substr(0, delimiterPos);
      auto value = pair.substr(delimiterPos + 1);
      keyValuePairs[key] = value;
    }
    start = end + 1;
  }

  auto lastPair = input.substr(start, input.size() - start - 1);
  auto delimiterPos = lastPair.find(':');
  if (delimiterPos != std::string::npos) {
    auto key = lastPair.substr(0, delimiterPos);
    auto value = lastPair.substr(delimiterPos + 1);
    keyValuePairs[key] = value;
  }

  return keyValuePairs;
}

void parseConfig(const std::string& fileName, int* port, std::string* path, int* seed) {
  std::ifstream file(fileName);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Не удалось открыть файл: " << fileName << std::endl;
    return;
  }

  while (std::getline(file, line)) {
    std::istringstream is_line(line);
    std::string key;
    if (std::getline(is_line, key, ':')) {
      std::string value;
      if (std::getline(is_line, value)) {
        if (key == "port") {
          *port = std::stoi(value);
        } else if (key == "path") {
          *path = value;
          size_t pos = path->find('\"');
          if (pos != std::string::npos) {
            path->erase(pos, 1);
          }
          pos = path->rfind('\"');
          if (pos != std::string::npos) {
            path->erase(pos, 1);
          }
        } else if (key == "seed") {
          *seed = std::stoi(value);
        }
      }
    }
  }

  file.close();
}