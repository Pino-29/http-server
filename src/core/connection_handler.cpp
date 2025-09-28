//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#include "core/connection_handler.hpp"

#include "../../include/core/request/request.hpp"
#include "../../include/core/request/request_parser.hpp"

#include "handlers.hpp"

#include <arpa/inet.h>   // For inet_ntoa()
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>  // For recv() and send()
#include <unistd.h>      // For close()

namespace http
{
    ConnectionHandler::ConnectionHandler(const int& socketFD, const sockaddr_in& clientAddr)
        : m_socketFD(socketFD),
          m_clientAddr(clientAddr),
          m_isConnected(true)
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
        Buffer buffer(1024, '\0'); // Fixed-size buffer
        ssize_t bytesReceived = recv(m_socketFD, buffer.data(), buffer.size(), 0);

        if (bytesReceived <= 0)
        {
            throw std::runtime_error("Failed to receive data or client disconnected.");
        }

        buffer.resize(bytesReceived);
        return buffer;
    }

    Response ConnectionHandler::routeRequest(const Request& request) const
    {
        switch (request.method)
        {
            case Method::GET:
                return getHandlerInstance().route(request);
            case Method::POST:
                return postHandlerInstance().route(request);
            default:
                return Response(StatusCode::NotImplemented);
        }
    }

    void ConnectionHandler::handle()
    {
        while (m_isConnected)
        {
            try
            {
                const auto buffer = readRequest();
                if (buffer.empty())
                {
                    // Client closed the connection gracefully
                    break;
                }

                const auto request = RequestParser(buffer).parse();

                if (request.getHeader("Connection") == "close")
                {
                    m_isConnected = false;
                }

                std::cout << "Creating response" << std::endl;
                Response response = routeRequest(request);
                std::cout << "Response completed" << std::endl;

                if (!m_isConnected)
                {
                    response.addHeader("Connection", "close");
                }

                std::string responseStr = response.toString();
                send(m_socketFD, responseStr.data(), responseStr.size(), 0);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error with client " << m_socketFD << ": " << e.what() << std::endl;
                break;
            }
        }
    }
}
