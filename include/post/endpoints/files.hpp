//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_FILES_H
#define HTTP_SERVER_STARTER_CPP_FILES_H

#include "../../core/request/request.hpp"

namespace http::post::endpoints
{
    std::string files(const Request& request);
}

#endif //HTTP_SERVER_STARTER_CPP_FILES_H