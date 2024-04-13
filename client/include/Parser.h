/**
 * @file Parser.h
 * @brief Provides a utility to parse structured messages.
 *
 * This utility function parses a formatted message string into a dictionary-like
 * structure for easy access to its components.
 */

#ifndef RIDDLE_CLIENT_INCLUDE_PARSER_H_
#define RIDDLE_CLIENT_INCLUDE_PARSER_H_

#include <string>
#include <unordered_map>
#include <stdexcept>

/**
 * @brief Parses a structured message into a key-value map.
 * @param input The string input formatted as a structured message.
 * @return A std::unordered_map where each key-value pair represents a component of the message.
 * @throws std::invalid_argument if the input string is improperly formatted.
 */
std::unordered_map<std::string, std::string> parseMessage(const std::string& input);

#endif // RIDDLE_CLIENT_INCLUDE_PARSER_H_
