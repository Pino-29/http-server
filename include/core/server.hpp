//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_SERVER_HPP
#define HTTP_SERVER_STARTER_CPP_SERVER_HPP

#include <core/socket_setup.hpp> // Your setup header
#include "core/types.hpp"
#include <netinet/in.h> // For sockaddr_in
#include <thread>
#include <unistd.h> // For close()

namespace http
{
    class Server
    {
    public:
        explicit Server(const sockets::ServerOptions& options);

        ~Server();

        [[noreturn]] void run() const;

    private:
        int m_serverFD {};
    };
}

#endif //HTTP_SERVER_STARTER_CPP_SERVER_HPP
