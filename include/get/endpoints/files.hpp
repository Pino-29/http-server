//
// Created by Roberto Jesus Garcia Pino on 10/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_FILES_H
#define HTTP_SERVER_STARTER_CPP_FILES_H

#include "../../core/request/request.hpp"
#include "../../../include/core/response/response.hpp"

namespace http::get::endpoints
{
    http::Response files(const Request& request);
}

#endif //HTTP_SERVER_STARTER_CPP_FILES_H
