#include "bind_socket.hpp"
#include "create_socket.hpp"
#include "http_get.hpp"
#include "http_request.hpp"

#include <cassert>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sstream>

using Buffer = std::string;

void handleResponse(const int& clientFD, const Buffer& buffer);

Buffer readRequest(const int& clientFD);

void handleConnection(const int& serverFD);

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

  handleConnection(serverFD);

  close(serverFD);
  return 0;
}

void handleResponse(const int& clientFD, const http::Request& request)
{
  // Safe & Idempotent Methods
  if (request.method == http::Method::GET)
  {
    http::get::processRequest(clientFD, request);
  }
  else if (request.method == http::Method::HEAD)
  {
    // intentionally empty
  }
  else if (request.method == http::Method::OPTIONS)
  {
    // intentionally empty
  }
  // Unsafe or State-Changing Methods
  else if (request.method == http::Method::PUT)
  {
    // intentionally empty
  }
  else if (request.method == http::Method::POST)
  {
    // intentionally empty
  }
  else if (request.method == http::Method::PATCH)
  {
    // intentionally empty
  }
  else if (request.method == http::Method::DELETE)
  {
    // intentionally empty
  }
  // Authentication & Control-Oriented Methods
  else if (request.method == http::Method::CONNECT)
  {
    // intentionally empty
  }
  else if (request.method == http::Method::TRACE)
  {
    // intentionally empty
  } else
  {
    std::cerr << "Unknown method: " << request.method << "\n";
    throw std::runtime_error("Unknown method");
  }
}


Buffer readRequest(const int& clientFD)
{
  Buffer buffer(1024, '\0');
  ssize_t bytesReceived = recv(clientFD, buffer.data(), buffer.size(), 0);

  if (bytesReceived == -1)
  {
    throw std::runtime_error("Error while reading message");
  }

  std::cout << "Received " << bytesReceived << " bytes\n";
  return buffer;
}

void handleConnection(const int& serverFD)
{
  struct sockaddr_in clientAddr{};
  int clientAddrLen { sizeof(clientAddr) };

  std::cout << "Waiting for a client to connect...\n";

  const int clientFD { accept(serverFD, reinterpret_cast<struct sockaddr*>(&clientAddr), reinterpret_cast<socklen_t *>(&clientAddrLen)) };

  std::cout << "Client connected\n";
  std::cout << "Client address: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << "\n";
  std::cout << "Client address length: " << clientAddrLen << "\n";
  std::cout << "Client address family: " << clientAddr.sin_family << "\n";
  std::cout << "Client address port: " << clientAddr.sin_port << "\n";

  http::Request request{};
  try
  {
    const Buffer& buffer { readRequest(clientFD) };
    request = std::move(http::parseRequest(buffer)) ;
  } catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what();
    throw;
  }

  handleResponse(clientFD, request);
}
