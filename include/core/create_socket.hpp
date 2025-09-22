//
// Created by Roberto Jesus Garcia Pino on 08/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_CREATE_SOCKET_H
#define HTTP_SERVER_STARTER_CPP_CREATE_SOCKET_H

#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <utility>
#include <sys/socket.h>

namespace sockets
{
    class CreateSocketException : public std::exception
    {
    public:
        explicit CreateSocketException(std::string msg = "Failed to create server socket") : m_message(std::move(msg))
        {
        }

        [[nodiscard]] const char *what() const noexcept override
        {
            return m_message.c_str();
        }

    private:
        std::string m_message {};
    };

    class SetSocketException : public std::exception
    {
    public:
        explicit SetSocketException(std::string msg = "Failed to set socket") : m_message(std::move(msg))
        {
        }

        [[nodiscard]] const char *what() const noexcept override
        {
            return m_message.c_str();
        }

    private:
        std::string m_message {};
    };

    inline int createSocket()
    {
        int serverFD = socket(AF_INET, SOCK_STREAM, 0);
        if (serverFD < 0)
        {
            throw CreateSocketException();
        }

        // Since the tester restarts your program quite often, setting SO_REUSEADDR
        // ensures that we don't run into 'Address already in use' errors
        constexpr int reuse { 1 };
        if (setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
        {
            throw SetSocketException();
        }

        return serverFD;
    }
}

#endif //HTTP_SERVER_STARTER_CPP_CREATE_SOCKET_H
