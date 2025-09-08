#include "bind_socket.hpp"
#include "create_socket.hpp"
#include "header_line_parts.hpp"

#include <cassert>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sstream>


using Buffer = std::string;



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


std::vector<std::string> splitBySpace(const std::string& input) {
  std::string word;
  std::vector<std::string> result;
  std::istringstream iss { input };
  while (iss >> word) {
    result.push_back(word);
  }

  return result;
}

std::vector<std::string> getRequestLine(const Buffer &buffer)
{
  std::istringstream iss { buffer };
  std::string line;
  std::getline(iss, line, '\r');
  assert(iss.peek() == '\n');
  auto requestLine = std::move(splitBySpace(line));

  // TODO
  // logger.print(requestLine);
  if (requestLine.size() != 3)
  {
    throw std::runtime_error("Invalid request line");
  }

  return requestLine;
}

void sendResponse(const int& clientFD, const Buffer& buffer)
{
  std::vector<std::string> requestLine{};
  try
  {
     requestLine = std::move(getRequestLine(buffer));
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    throw;
  }

  // TODO: add logger
  // logger.print(requestLine);

  std::string_view response = "HTTP/1.1 200 OK\r\n\r\n";

  constexpr size_t target { static_cast<size_t>(RequestLineParts::kTarget) };
  std::string_view path { requestLine[target] };

  std::cout << "Path: " << path << "\n";
  if (path != "/")
  {
    response = "HTTP/1.1 404 Not Found\r\n\r\n";
  }

  send(clientFD, response.data(), response.size(), 0);
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

  const Buffer& buffer { readRequest(clientFD) };
  sendResponse(clientFD, buffer);
}

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
