//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_ECHO_H
#define HTTP_SERVER_STARTER_CPP_ECHO_H

#include "../../core/request/request.hpp"
#include "../../core/response/response.hpp"

namespace http::get::endpoints
{
    Response echo(const Request& request);
}

#endif //HTTP_SERVER_STARTER_CPP_ECHO_H
