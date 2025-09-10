//
// Created by Roberto Jesus Garcia Pino on 08/09/25.
//
#include "echo.hpp"

#include <iostream>
#include <ostream>

#include "http_request.hpp"

#include <string>

namespace http::get
{
    std::string echo(const Request& request)
    {
        std::string_view echoString = request.target;
        echoString.remove_prefix(6); // removes /echo/

        std::string response{};
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
