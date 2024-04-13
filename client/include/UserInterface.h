/**
 * @file UserInterface.h
 * @brief Manages the user interface for the client application.
 *
 * This class provides static methods to display messages, get user inputs,
 * and manage the console display, such as clearing the screen or displaying structured data.
 */

#ifndef RIDDLE_CLIENT_INCLUDE_USERINTERFACE_H_
#define RIDDLE_CLIENT_INCLUDE_USERINTERFACE_H_

#include <iostream>
#include <string>
#include <regex>

class UserInterface {
 public:
  /**
   * @brief Displays a welcome message to the user upon successful connection.
   */
  static void displayWelcomeMessage() {
    std::cout << "Connected to the server successfully.\n";
  }

  /**
   * @brief Gets user input with validation.
   * @param prompt The message to display to the user.
   * @return A valid string input from the user.
   * @details Only accepts up to 32 Latin letters without spaces or numbers.
   */
  static std::string getUserInput(const std::string& prompt) {
    std::regex validInput("^[A-Za-z]{1,32}$");
    std::string input;

    while (true) {
      std::cout << prompt;
      std::getline(std::cin, input);

      if (std::regex_match(input, validInput)) {
        break;
      } else {
        std::cout << "Invalid input. Please enter up to 32 Latin letters with no spaces or numbers.\n";
      }
    }

    return input;
  }

  /**
   * @brief Displays a message to the user.
   * @param message The message to display.
   */
  static void displayMessage(const std::string& message) {
    std::cout << message << std::endl;
  }

  /**
   * @brief Displays a riddle's description to the user.
   * @param description The description of the riddle.
   */
  static void displayRiddle(const std::string& description) {
    std::cout << "Riddle: " << description << std::endl;
  }

  /**
   * @brief Clears the console screen.
   */
  static void clearScreen() {
    system("clear");
  }
};


#endif //RIDDLE_CLIENT_INCLUDE_USERINTERFACE_H_
