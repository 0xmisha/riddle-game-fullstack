#ifndef RIDDLE_CLIENT_INCLUDE_USERINTERFACE_H_
#define RIDDLE_CLIENT_INCLUDE_USERINTERFACE_H_

#include <iostream>
#include <string>
#include <regex>

class UserInterface {
 public:
  static void displayWelcomeMessage() {
    std::cout << "Connected to the server successfully.\n";
  }

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

  static void displayMessage(const std::string& message) {
    std::cout << message << std::endl;
  }

  static void displayRiddle(const std::string& description) {
    std::cout << "Riddle: " << description << std::endl;
  }

  static void clearScreen() {
    system("clear");
  }
};


#endif //RIDDLE_CLIENT_INCLUDE_USERINTERFACE_H_
