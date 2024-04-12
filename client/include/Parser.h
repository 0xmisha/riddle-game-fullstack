#ifndef RIDDLE_CLIENT_INCLUDE_PARSER_H_
#define RIDDLE_CLIENT_INCLUDE_PARSER_H_

#include <string>
#include <unordered_map>
#include <stdexcept>

std::unordered_map<std::string, std::string> parseMessage(const std::string& input);

#endif //RIDDLE_CLIENT_INCLUDE_PARSER_H_
