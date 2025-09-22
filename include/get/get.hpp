//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_GET_H
#define HTTP_SERVER_STARTER_CPP_GET_H

#include "core/request.hpp"

namespace http::get
{
    void processRequest(const size_t& clientFD, const Request& request);
}
#endif //HTTP_SERVER_STARTER_CPP_GET_H