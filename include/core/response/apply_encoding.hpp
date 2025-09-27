//
// Created by Roberto Jesus Garcia Pino on 26/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_APPLY_ENCODING_HPP
#define HTTP_SERVER_STARTER_CPP_APPLY_ENCODING_HPP

#include "core/request/request.hpp"
#include "core/response/response.hpp"

namespace http
{
    void applyEncoding(const Request& request, Response& response);
}

#endif //HTTP_SERVER_STARTER_CPP_APPLY_ENCODING_HPP
