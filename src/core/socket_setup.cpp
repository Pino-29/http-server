//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#include "core/socket_setup.hpp"

#include "core/bind_socket.hpp"
#include "core/create_socket.hpp"

#include <iostream>
#include <stdexcept>
#include <unistd.h>

int sockets::setupServerSocket(const ServerOptions& options)
{
    int serverFD = -1;
    try
    {
        serverFD = createSocket();
        bindSocket(serverFD, options.port);

        if (listen(serverFD, options.connectionBacklog) != 0)
        {
            throw std::runtime_error("listen() failed");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error during socket setup: " << e.what() << std::endl;
        if (serverFD != -1)
        {
            close(serverFD);
        }

        return -1;
    }

    std::cout << "Server is listening on port " << options.port << "...\n";
    return serverFD;
}
