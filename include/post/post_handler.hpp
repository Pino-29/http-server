//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_POST_H
#define HTTP_SERVER_STARTER_CPP_POST_H

#include "core/request.hpp"

namespace http::post
{
    void handleRequest(const size_t& clientFD, const Request& request);
}

#endif //HTTP_SERVER_STARTER_CPP_POST_H
