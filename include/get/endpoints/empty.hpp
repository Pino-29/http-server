//
// Created by Roberto Jesus Garcia Pino on 23/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_EMPTY_HPP
#define HTTP_SERVER_STARTER_CPP_EMPTY_HPP

#include "core/request/request.hpp"
#include "core/response/response.hpp"

namespace http::get::endpoints
{
    Response empty(const Request& request);
}

#endif //HTTP_SERVER_STARTER_CPP_EMPTY_HPP
