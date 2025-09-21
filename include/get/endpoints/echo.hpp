//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_ECHO_H
#define HTTP_SERVER_STARTER_CPP_ECHO_H

#include "request.hpp"

#include <string>

namespace http::get::endpoints
{
    std::string echo(const Request& request);
}
#endif //HTTP_SERVER_STARTER_CPP_ECHO_H