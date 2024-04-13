#include "include/MainClient.h"

#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[]) {
  std::string ip = "127.0.0.1";
  int port = 8085;
  int opt;

  while ((opt = getopt(argc, argv, "a:p:")) != -1) {
    switch (opt) {
      case 'a':
        ip = optarg;
        break;
      case 'p':
        port = std::atoi(optarg);
        if (port <= 0 || port > 65535) {
          std::cerr << "Invalid port number. Please enter a number between 1 and 65535." << std::endl;
          return 1;
        }
        break;
      default:
        std::cerr << "Usage: " << argv[0] << " -a <ip_address> -p <port>" << std::endl;
        return 1;
    }
  }

  if (optind < argc) {
    std::cerr << "Expected argument after options." << std::endl;
    return 1;
  }

  try {
    MainClient client(ip, port);
    client.startGame();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}

