#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
  int port = 8081;
  const char *address = "127.0.0.1";

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Could not create socket" << std::endl;
    return -1;
  }

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);
  serverAddress.sin_addr.s_addr = inet_addr(address);

  if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
    std::cerr << "Connect failed" << std::endl;
    return -1;
  }

  std::cout << "Connected to the server" << std::endl;

  char input;
  do {
    std::string message;
    std::cout << "Enter message to send (or 'Z' to quit): ";
    std::cin >> input;
    if (input == 'Z')
      break;
    if (input == '1') message = "type:start,name:misha.";
    if (input == '2') message = "type:guess,word:xuy.";
    if (input == '3') message = "type:hint.";
    if (input == '4') message = "type:surrender.";

    if (send(sock, message.c_str(), message.size(), 0) < 0) {
      std::cerr << "Send failed" << std::endl;
      return -1;
    }

    char buffer[1024] = {0};
    ssize_t bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived <= 0) {
      std::cerr << "Server has closed the connection" << std::endl;
      break;
    }

    std::cout << buffer << std::endl;
  } while (input != 'Z');

  close(sock);

  return 0;
}
