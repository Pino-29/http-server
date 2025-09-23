//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#include "core/connection_handler.hpp"

#include "core/request.hpp"
#include "core/request_parser.hpp"
#include "get/get_handler.hpp"
#include "post/post_handler.hpp"

#include <arpa/inet.h>   // For inet_ntoa()
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>  // For recv() and send()
#include <unistd.h>      // For close()

namespace http
{
    ConnectionHandler::ConnectionHandler(const int& socketFD, const sockaddr_in& clientAddr)
        : m_socketFD(socketFD),
          m_clientAddr(clientAddr)
    {
        std::cout << "Connection opened for client " << m_socketFD << " from "
                << inet_ntoa(m_clientAddr.sin_addr) << ":"
                << ntohs(m_clientAddr.sin_port) << "\n";
    }

    ConnectionHandler::~ConnectionHandler()
    {
        if (m_socketFD != -1)
        {
            close(m_socketFD);
            std::cout << "Connection closed for client " << m_socketFD << "\n";
        }
    }

    [[nodiscard]] Buffer ConnectionHandler::readRequest() const
    {
        std::string buffer(1024, '\0'); // Fixed-size buffer
        ssize_t bytesReceived = recv(m_socketFD, buffer.data(), buffer.size(), 0);

        if (bytesReceived <= 0)
        {
            throw std::runtime_error("Failed to receive data or client disconnected.");
        }

        buffer.resize(bytesReceived);
        return buffer;
    }

    void ConnectionHandler::routeRequest(const Request& request) const
    {
        switch (request.method)
        {
            case Method::GET:
                get::handleRequest(m_socketFD, request);
                break;
            case Method::POST:
                post::handleRequest(m_socketFD, request);
                break;
            default:
                send(m_socketFD, "HTTP/1.1 501 Not Implemented\r\n\r\n", 35, 0);
                break;
        }
    }

    void ConnectionHandler::handle()
    {
        try
        {
            const auto buffer = readRequest();
            const auto request = RequestParser(buffer).parse();
            routeRequest(request);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error handling client " << m_socketFD << ": " << e.what() << std::endl;
            send(m_socketFD, "HTTP/1.1 400 Bad Request\r\n\r\n", 26, 0);
        }
    }
}
