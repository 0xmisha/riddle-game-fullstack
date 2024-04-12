#include "../include/ClientNetworkHandler.h"

ClientNetworkHandler::ClientNetworkHandler(const std::string& ip, int port) {
  if (!isValidIpAddress(ip)) {
    throw std::invalid_argument("Invalid IP address");
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Could not create socket" << std::endl;
    throw std::runtime_error("Socket creation failed");
  }

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);
  serverAddress.sin_addr.s_addr = inet_addr(ip.c_str());

  if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
    throw std::runtime_error("Connection failed. Check server IP.");
  }
}

ClientNetworkHandler::~ClientNetworkHandler() {
  close(sock);
}

void ClientNetworkHandler::sendMessage(const std::string& message) {
  if (send(sock, message.c_str(), message.size(), 0) < 0) {
    std::cerr << "Send failed" << std::endl;
    throw std::runtime_error("Send failed");
  }
}

std::string ClientNetworkHandler::receiveMessage() {
  char buffer[1024] = {0};
  ssize_t bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (bytesReceived <= 0) {
    std::cerr << "Server has closed the connection" << std::endl;
    throw std::runtime_error("Receive failed or connection closed");
  }
  return std::string(buffer, bytesReceived);
}

bool ClientNetworkHandler::isValidIpAddress(const std::string& ip) {
  struct sockaddr_in sa;
  int result = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
  return result != 0;
}