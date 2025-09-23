//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#include "get/endpoints/user_agent.hpp"

#include "../../../include/core/request/request.hpp"

#include <string>

namespace http::get::endpoints
{
    std::string userAgent(const Request& request)
    {
        const std::string body { request.getHeader("User-Agent") };
        std::string response {};
        // status line
        response += "HTTP/1.1 200 OK";
        response += "\r\n";
        // headers
        response += "Content-Type: text/plain\r\n";
        response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
        response += "\r\n";
        // body
        response += body;
        return response;
    }
}
