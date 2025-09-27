//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_USER_AGENT_H
#define HTTP_SERVER_STARTER_CPP_USER_AGENT_H

#include "../../core/request/request.hpp"
#include "core/response/response.hpp"

#include <string>

namespace http::get::endpoints
{
    Response userAgent(const Request& request);
}

#endif //HTTP_SERVER_STARTER_CPP_USER_AGENT_H
