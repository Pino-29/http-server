//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#include "http_get.hpp"

#include "http_request.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <sys/socket.h>

#include "echo.hpp"

namespace http::get
{
    void processRequest(const size_t& clientFD, const Request& request)
    {
        assert(request.method == Method::GET);

        std::string response{};
        if (request.target == "/")
        {
            response = "HTTP/1.1 200 OK\r\n\r\n";
        }
        else if (request.target.starts_with("/echo/"))
        {
            response = endpoint::echo(request);
        }
        else // random unknown path
        {
            response = "HTTP/1.1 404 Not Found\r\n\r\n";
        }

        send(clientFD, response.data(), response.size(), 0);
    }
}
