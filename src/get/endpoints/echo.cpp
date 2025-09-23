//
// Created by Roberto Jesus Garcia Pino on 08/09/25.
//

#include "get/endpoints/echo.hpp"

#include "core/request.hpp"

#include <ostream>
#include <string>

namespace http::get::endpoints
{
    std::string emptyReply()
    {
        return "HTTP/1.1 200 OK\r\n\r\n";
    }

    std::string echo(const Request& request)
    {
        std::string_view echoString = request.target;
        constexpr std::string_view prefix { "/echo/" };
        if (!echoString.starts_with(prefix) || echoString.size() == prefix.size())
        {
            return emptyReply();
        }

        echoString.remove_prefix(prefix.size());
        std::string response {};
        response += "HTTP/1.1 200 OK";
        response += "\r\n";
        // headers
        response += "Content-Type: text/plain\r\n";
        response += "Content-Length: " + std::to_string(echoString.size()) + "\r\n";
        response += "\r\n";
        // body
        response += echoString;
        return response;
    }
}
