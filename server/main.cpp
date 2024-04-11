#include "include/MainServer.h"

#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
  std::string configFile = "server.cfg";
  int port = 8081;
  std::string path = "../../server/riddles";
  int seed = 42;

  int opt;
  while ((opt = getopt(argc, argv, "f:p:s:d:")) != -1) {
    switch (opt) {
      case 'f': parseConfig(optarg, &port, &path, &seed); break;
      case 'p': port = std::stoi(optarg); break;
      case 's': path = optarg; break;
      case 'd': seed = std::stoi(optarg); break;
      default:
        std::cerr << "Usage: " << argv[0] << " [-f configFile] [-p port] [-s path] [-d seed]\n";
        exit(EXIT_FAILURE);
    }
  }

  MainServer server(port, path, seed);
  server.acceptConnections();
  return 0;
}
