//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#include "core/server.hpp"


#include "core/connection_handler.hpp"
#include "../../include/core/request/request.hpp"
#include "../../include/core/sockets/socket_setup.hpp"

#include <cassert>
#include <iostream>
#include <netinet/in.h>
#include <thread>
#include <tuple>
#include <unistd.h>
#include <unordered_map>

namespace http
{
    Server::Server(const sockets::ServerOptions& options)
    {
        m_serverFD = sockets::setupServerSocket(options);
        if (m_serverFD == -1)
        {
            throw std::runtime_error("Failed to set up the server socket.");
        }
    }

    Server::~Server()
    {
        if (m_serverFD != -1)
        {
            close(m_serverFD);
        }
    }

    [[noreturn]] void Server::run() const
    {
        while (true)
        {
            std::cout << "Waiting for a client to connect...\n";

            struct sockaddr_in clientAddr {};
            socklen_t clientAddrLen { sizeof(clientAddr) };
            const int clientFD = accept(m_serverFD,
                                        reinterpret_cast<struct sockaddr *>(&clientAddr),
                                        &clientAddrLen);

            if (clientFD < 0)
            {
                std::cerr << "Error: accept failed\n";
                continue;
            }

            std::thread([clientFD, clientAddr]()
            {
                try
                {
                    http::ConnectionHandler handler(clientFD, clientAddr);
                    handler.handle();
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Exception in client thread: " << e.what() << std::endl;
                }
            }).detach();
        }
    }
}
