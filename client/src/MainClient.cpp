#include "../include/MainClient.h"

MainClient::MainClient(const std::string& ip, int port) : networkHandler(ip, port) {
  UserInterface::displayWelcomeMessage();
}

void MainClient::startGame() {
  try {
    std::string name = UserInterface::getUserInput("Please enter your name: ");
    UserInterface::clearScreen();

    std::string startMessage = "type:start,name:" + name + ".";
    networkHandler.sendMessage(startMessage);

    std::string serverResponse = networkHandler.receiveMessage();
    auto responseParts = parseMessage(serverResponse);

    if (responseParts["type"] == "riddle") {
      riddle = responseParts["description"];
      UserInterface::displayRiddle(riddle);

      int attemptsLeft = 3;
      while (attemptsLeft > 0) {
        std::string userAnswer = UserInterface::getUserInput("Answer the riddle or request a 'hint' or 'surrender': ");
        UserInterface::clearScreen();
        UserInterface::displayRiddle(riddle);

        if (userAnswer == "hint") {
          requestHint();
        } else if (userAnswer == "surrender") {
          surrender();
          break;
        } else {
          makeGuess(userAnswer);
          serverResponse = networkHandler.receiveMessage();
          responseParts = parseMessage(serverResponse);

          if (responseParts["type"] == "result") {
            if (responseParts["status"] == "correct") {
              UserInterface::displayMessage("Congratulations! You've guessed the riddle.");
              break;
            }
            if (responseParts["attemptsLeft"] != "0") {
              UserInterface::displayMessage("Wrong! You have  " + responseParts["attemptsLeft"] + " attempts left");
            }
            attemptsLeft = std::stoi(responseParts["attemptsLeft"]);
          }
        }

        if (attemptsLeft == 0) {
          UserInterface::displayMessage("No attempts left, surrendering...");
          surrender();
          break;
        }
      }
    } else if (responseParts["type"] == "error") {
      if (responseParts["cause"] == "user_already_playing")
        UserInterface::displayMessage("Error! User with same name is already playing.");
    }
  } catch (const std::exception& e) {
    UserInterface::displayMessage(e.what());
  }
}

void MainClient::makeGuess(const std::string& word) {
  try {
    std::string guessMessage = "type:guess,word:" + word + ".";
    networkHandler.sendMessage(guessMessage);

  } catch (const std::exception& e) {
    UserInterface::displayMessage(e.what());
  }
}

void MainClient::requestHint() {
  try {
    std::string hintMessage = "type:hint.";
    networkHandler.sendMessage(hintMessage);

    std::string serverResponse = networkHandler.receiveMessage();
    auto responseParts = parseMessage(serverResponse);

    if (responseParts["type"] == "hint") {
      std::string hint = responseParts["hint"];
      if (hint == "No hints left") {
        UserInterface::displayMessage("You have no hints left");
      } else {
        UserInterface::displayMessage("Hint: " + hint);
      }
    }
  } catch (const std::exception& e) {
    UserInterface::displayMessage(e.what());
  }
}

void MainClient::surrender() {
  try {
    std::string surrenderMessage = "type:surrender.";
    networkHandler.sendMessage(surrenderMessage);

    std::string serverResponse = networkHandler.receiveMessage();
    auto responseParts = parseMessage(serverResponse);

    if (responseParts["type"] == "answer") {
      std::string word = responseParts["word"];
      UserInterface::displayMessage("The correct word was: " + word);
    }
  } catch (const std::exception& e) {
    UserInterface::displayMessage(e.what());
  }
}