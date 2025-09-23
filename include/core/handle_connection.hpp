//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_HANDLE_CONNECTION_HPP
#define HTTP_SERVER_STARTER_CPP_HANDLE_CONNECTION_HPP

namespace http
{
    void handleConnection(const int& socket_fd, const sockaddr_in& clientAddr);
}

#endif //HTTP_SERVER_STARTER_CPP_HANDLE_CONNECTION_HPP