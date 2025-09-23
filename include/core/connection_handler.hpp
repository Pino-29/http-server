//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_CONNECTION_HANDLER_HPP
#define HTTP_SERVER_STARTER_CPP_CONNECTION_HANDLER_HPP

#include "request/request.hpp"
#include "core/types.hpp"

#include <netinet/in.h>

namespace http
{
    // Manages the lifecycle and logic for a single client connection.
    class ConnectionHandler
    {
    public:
        ConnectionHandler(const int& socketFD, const sockaddr_in& clientAddr);

        ~ConnectionHandler(); // Destructor will close the socket.

        // Disallow copying to prevent accidental socket duplication.
        ConnectionHandler(const ConnectionHandler&) = delete;

        ConnectionHandler& operator=(const ConnectionHandler&) = delete;

        // The main entry point to handle the request.
        void handle();

    private:
        int m_socketFD;
        sockaddr_in m_clientAddr;

        [[nodiscard]] Buffer readRequest() const;

        void routeRequest(const Request& request) const;
    };
}

#endif //HTTP_SERVER_STARTER_CPP_CONNECTION_HANDLER_HPP
