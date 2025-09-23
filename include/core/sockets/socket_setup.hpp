//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_SOCKET_SETUP_HPP
#define HTTP_SERVER_STARTER_CPP_SOCKET_SETUP_HPP

namespace sockets
{
    struct ServerOptions
    {
        int port {};
        int connectionBacklog { 5 };
    };

    int setupServerSocket(const ServerOptions& options);
}

#endif //HTTP_SERVER_STARTER_CPP_SOCKET_SETUP_HPP
