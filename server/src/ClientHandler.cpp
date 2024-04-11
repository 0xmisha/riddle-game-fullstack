#include "../include/ClientHandler.h"

void ClientHandler::operator()(int clientSocket) {
  std::cout << "Handling client in thread " << std::this_thread::get_id() << std::endl;
  std::string messageStr, partialRequest;

  while (true) {
    partialRequest = ServerNetworkHandler::receiveRequest(clientSocket);
    if (partialRequest.empty()) {
      std::cout << "Client in thread " << std::this_thread::get_id() << " disconnected" << std::endl;
      break;
    }

    messageStr.append(partialRequest);

    size_t endPos;
    while ((endPos = messageStr.find('.')) != std::string::npos) {
      std::string singleMessage = messageStr.substr(0, endPos + 1);
      messageStr.erase(0, endPos + 1);

      if (!processMessage(singleMessage, clientSocket)) {
        close(clientSocket);
        return;
      }
    }
  }
  close(clientSocket);
}

bool ClientHandler::processMessage(const std::string& messageStr, int clientSocket) {
  try {
    auto message = parseMessage(messageStr);

    std::string responseStr;

    if (message.find("type") != message.end()) {
      if (message["type"] == "start") {
        std::string name;
        if (message.find("name") != message.end()) {
          clientName = message["name"];
          gameManager.chooseRiddle();
          responseStr = "type:riddle,description:" + gameManager.getCurrentRiddleDescription() + ".";
        }
      } else if (message["type"] == "guess") {
        std::string word;
        if (message.find("word") != message.end()) {
          bool isCorrect = gameManager.checkGuess(message["word"]);
          std::string status = isCorrect ? "correct" : "wrong";
          responseStr = "type:result,status:" + status + ",attemptsLeft:" + std::to_string(gameManager.getAttemptsLeft()) + ".";
        }
      } else if (message["type"] == "hint") {
        responseStr = "type:hint,hint:" + gameManager.getHint() + ".";
      }  else if (message["type"] == "surrender") {
        responseStr = "type:answer,word:" + gameManager.getWord() + ".";
      } else {
        responseStr = "Bad request.";
      }
    } else {
      responseStr = "Bad request.";
    }

    ServerNetworkHandler::sendResponse(clientSocket, responseStr);
  } catch (const std::exception& e) {
    std::cerr << "Failed to parse message: " << e.what() << '\n';
    return false;
  }

  return true;
}