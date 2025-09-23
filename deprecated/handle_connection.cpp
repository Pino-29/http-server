//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#include "handle_connection.hpp"

#include "core/request.hpp"
#include "core/types.hpp"
#include "get/get_handler.hpp"
#include "post/post_handler.hpp"

#include <iostream>
#include <unistd.h>
#include <netinet/in.h>


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

void http::handleConnection(const int& socket_fd, const sockaddr_in& clientAddr)
{
    std::cout << "Handling client " << socket_fd << "\n";

    std::cout << "Client connected\n";
    std::cout << "Client connected from " << inet_ntoa(clientAddr.sin_addr) << ":"
            << ntohs(clientAddr.sin_port) << "\n";
    std::cout << "Client address: " << clientAddr.sin_addr.s_addr << "\n";
    std::cout << "Client port: " << ntohs(clientAddr.sin_port) << "\n";
    http::Request request {};
    try
    {
        const Buffer& buffer { readRequest(socket_fd) };
        request = http::parseRequest(buffer);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what();
        send(socket_fd, "HTTP/1.1 400 Bad Request\r\n\r\n", 39, 0);
        return;
    }

    switch (request.method)
    {
        case Method::GET:
            get::handleRequest(socket_fd, request);
            break;
        case Method::POST:
            post::handleRequest(socket_fd, request);
            break;
        case Method::HEAD:
        case Method::OPTIONS:
        case Method::PUT:
        case Method::PATCH:
        case Method::DELETE:
            sendResponse(socket_fd, "HTTP/1.1 501 Not Implemented\r\n\r\n");
            break;
        default:
            std::cerr << "Unknown or unsupported method\n";
            sendResponse(socket_fd, "HTTP/1.1 400 Bad Request\r\n\r\n");
            break;
    }

    close(clientFD);
}
