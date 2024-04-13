/**
 * @file Parser.h
 * @brief Provides utility functions for parsing configurations and messages.
 *
 * Contains functions to parse configuration files and structured messages,
 * converting them into useable formats within the application.
 */

#ifndef RIDDLE_SERVER_INCLUDE_PARSER_H_
#define RIDDLE_SERVER_INCLUDE_PARSER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <limits>
#include <sys/stat.h>

/**
 * @brief Parses a structured message into a key-value map.
 * @param input The structured message string.
 * @return A map of key-value pairs extracted from the message.
 */
std::unordered_map<std::string, std::string> parseMessage(const std::string& input);

/**
 * @brief Parses the configuration file for server settings.
 * @param fileName Path to the configuration file.
 * @param port Pointer to store the parsed port number.
 * @param path Pointer to store the parsed path to riddle files.
 * @param seed Pointer to store the parsed seed for random number generation.
 */
void parseConfig(const std::string& fileName, int* port, std::string* path, int* seed);

#endif // RIDDLE_SERVER_INCLUDE_PARSER_H_
