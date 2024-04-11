#include "../include/MainServer.h"

MainServer::MainServer(int port, const std::string& pathToRiddles, unsigned int seed) : port(port), pathToRiddles(pathToRiddles), seed(seed) {
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    exit(EXIT_FAILURE);
  }

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);

  if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
    std::cerr << "Failed to bind" << std::endl;
    close(serverSocket);
    exit(EXIT_FAILURE);
  }

  if (listen(serverSocket, 10) == -1) {
    std::cerr << "Failed to listen" << std::endl;
    close(serverSocket);
    exit(EXIT_FAILURE);
  }
}

void MainServer::acceptConnections() {
  std::cout << "Server is listening on port " << port << std::endl;

  while (true) {
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1) {
      std::cerr << "Failed to accept client connection" << std::endl;
      continue;
    }
    std::thread clientThread([this, clientSocket]() {
      ClientHandler handler(pathToRiddles, seed);
      handler(clientSocket);
    });
    clientThread.detach();
  }
}