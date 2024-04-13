#include "include/MainServer.h"

#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
  std::string configFile = "default";
  int port = 8085;
  std::string path = "../../server/riddles";
  int seed = 42;

  int opt;
  while ((opt = getopt(argc, argv, "f:")) != -1) {
    switch (opt) {
      case 'f': configFile = optarg;; break;
      default:
        std::cerr << "Usage: " << argv[0] << " [-f configFile]\n";
        exit(EXIT_FAILURE);
    }
  }

  try {
    if (configFile != "default") parseConfig(configFile, &port, &path, &seed);
    MainServer server(port, path, seed);
    server.acceptConnections();
  } catch (const std::exception& e) {
    std::cerr << "Server initialization failed: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
