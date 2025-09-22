//
// Created by Roberto Jesus Garcia Pino on 08/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_BIND_SOCKET_H
#define HTTP_SERVER_STARTER_CPP_BIND_SOCKET_H


#include <arpa/inet.h>
#include <iostream>
#include <utility>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

namespace sockets
{
    class BindException : public std::exception
    {
    public:
        explicit BindException(std::string  msg = "Failed to bind to port") : m_message(std::move(msg)) {}

        [[nodiscard]] const char* what() const noexcept override
        {
            return m_message.c_str();
        }

    private:
        std::string m_message{};
    };

    inline sockaddr_in bindSocket(const int& serverFD, const int& port = 4221)
    {
        struct sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(serverFD, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) != 0)
        {
            throw BindException("Failed to bind to port " + std::to_string(port));
        }

        return serverAddr;
    }
}

#endif //HTTP_SERVER_STARTER_CPP_BIND_SOCKET_H