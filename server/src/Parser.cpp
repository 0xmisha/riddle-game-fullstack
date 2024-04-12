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

bool directoryExists(const std::string& path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0)
    return false;
  return (info.st_mode & S_IFDIR) != 0;
}

void parseConfig(const std::string& fileName, int* port, std::string* path, int* seed) {
  std::ifstream file(fileName);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Cant open file: " << fileName << std::endl;
    return;
  }

  while (std::getline(file, line)) {
    std::istringstream is_line(line);
    std::string key;
    if (std::getline(is_line, key, ':')) {
      std::string value;
      if (std::getline(is_line, value)) {
        value.erase(0, value.find_first_not_of(" \t"));
        if (key == "port") {
          try {
            int parsedPort = std::stoi(value);
            if (parsedPort < 1 || parsedPort > 65535) {
              std::cerr << "Invalid port number. Please enter a number between 1 and 65535." << std::endl;
            } else {
              *port = parsedPort;
            }
          } catch (const std::exception& e) {
            std::cerr << "Invalid port number: " << value << std::endl;
          }
        } else if (key == "path") {
          if (directoryExists(value)) {
            *path = value;
          } else {
            std::cerr << "Directory doesnt exist: " << value << std::endl;
          }
        } else if (key == "seed") {
          try {
            *seed = std::stoi(value);
          } catch (const std::exception& e) {
            std::cerr << "Incorrect seed value: " << value << std::endl;
          }
        }
      }
    }
  }

  file.close();
}