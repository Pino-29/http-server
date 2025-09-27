//
// Created by Roberto Jesus Garcia Pino on 26/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_GET_ENDPOINT_HPP
#define HTTP_SERVER_STARTER_CPP_GET_ENDPOINT_HPP

#include <string>
#include <string_view>

namespace http
{
    std::string getEndpoint(std::string_view target);
}

#endif //HTTP_SERVER_STARTER_CPP_GET_ENDPOINT_HPP
