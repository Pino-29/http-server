#include "bind_socket.h"
#include "create_socket.h"

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char **argv) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  
  // You can use print statements as follows for debugging, they'll be visible when running tests.
  std::cout << "Logs from your program will appear here!\n";

  int serverFD{};
  try
  {
    serverFD = sockets::createSocket();
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  try
  {
    constexpr int port { 4221 };
    sockets::bindSocket(serverFD, port);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  constexpr int connectionBacklog { 5 };
  if (listen(serverFD, connectionBacklog) != 0) {
    std::cerr << "listen failed\n";
    return 1;
  }

  struct sockaddr_in clientAddr{};
  int clientAddrLen = sizeof(clientAddr);

  std::cout << "Waiting for a client to connect...\n";

  accept(serverFD, reinterpret_cast<struct sockaddr*>(&clientAddr), reinterpret_cast<socklen_t *>(&clientAddrLen));
  std::cout << "Client connected\n";

  close(serverFD);
  return 0;
}
