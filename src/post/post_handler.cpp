//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#include "post/post_handler.hpp"

#include "core/request.hpp"
#include "post/endpoints/files.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace http::post
{
    std::string getEndpoint(const std::string& input)
    {
        std::stringstream ss(input);
        std::string token {};

        ss.ignore(1, '/');
        std::getline(ss, token, '/');

        return token;
    }

    void handleRequest(const size_t& clientFD, const Request& request)
    {
        assert(request.method == Method::POST);

        std::cout << "POST\n";
        std::string endpoint { getEndpoint(request.target) };

        std::cout << "Endpoint: " << endpoint << "\n";
        std::string response {};

        if (endpoint == "files")
        {
            response = endpoints::files(request);
        }
        else // random unknown path
        {
            response = "HTTP/1.1 404 Not Found\r\n\r\n";
        }

        send(clientFD, response.data(), response.size(), 0);
    }
}
