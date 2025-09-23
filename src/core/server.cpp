//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#include "core/server.hpp"

#include "core/connection_handler.hpp"
#include "core/request.hpp"
#include "core/socket_setup.hpp"

#include <iostream>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>

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

    void handleConnectionThread(int clientFD, sockaddr_in clientAddr)
    {
        try
        {
            http::ConnectionHandler handler(clientFD, clientAddr);
            handler.handle();
        }
        catch (const std::exception& e)
        {
            std::cerr << "Unhandled exception in client thread: " << e.what() << std::endl;
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

            std::thread(handleConnectionThread, clientFD, clientAddr).detach();
        }
    }
}
