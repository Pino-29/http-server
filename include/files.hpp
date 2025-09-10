//
// Created by Roberto Jesus Garcia Pino on 10/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_FILES_H
#define HTTP_SERVER_STARTER_CPP_FILES_H

#include "http_request.hpp"

#include <string>

namespace http::get::endpoint
{
    std::string files(const Request& request);
}

#endif //HTTP_SERVER_STARTER_CPP_FILES_H