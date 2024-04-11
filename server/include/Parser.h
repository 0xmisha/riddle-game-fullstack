#ifndef RIDDLE_SERVER_INCLUDE_PARSER_H_
#define RIDDLE_SERVER_INCLUDE_PARSER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

std::unordered_map<std::string, std::string> parseMessage(const std::string& input);

void parseConfig(const std::string& fileName, int* port, std::string* path, int* seed);

#endif //RIDDLE_SERVER_INCLUDE_PARSER_H_
