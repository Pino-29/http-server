//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#include "get.hpp"

#include "echo.hpp"
#include "request.hpp"
#include "user_agent.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sstream>
#include <unistd.h>

#include "files.hpp"

namespace http::get
{
    std::string getEndpoint(const std::string& input)
    {
        std::stringstream ss(input);
        std::string token {};

        ss.ignore(1, '/');
        !std::getline(ss, token, '/');

        return token;
    }

    void processRequest(const size_t& clientFD, const Request& request)
    {
        assert(request.method == Method::GET);
        std::string endpoint { getEndpoint(request.target) };
        std::string response {};

        if (endpoint.empty())
        {
            response = "HTTP/1.1 200 OK\r\n\r\n";
        }
        else if (endpoint == "echo")
        {
            response = endpoint::echo(request);
        }
        else if (endpoint == "user-agent")
        {
            response = endpoint::userAgent(request);
        }
        else if (endpoint == "files")
        {
            response = endpoint::files(request);
        }
        else // random unknown path
        {
            response = "HTTP/1.1 404 Not Found\r\n\r\n";
        }

        send(clientFD, response.data(), response.size(), 0);
    }
}
