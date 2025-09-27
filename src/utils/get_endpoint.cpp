//
// Created by Roberto Jesus Garcia Pino on 26/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_GET_ENDPOINT_HPP
#define HTTP_SERVER_STARTER_CPP_GET_ENDPOINT_HPP

#include "utils/get_endpoint.hpp"

#include <string>
#include <string_view>

namespace http
{
    std::string getEndpoint(std::string_view target)
    {
        if (target.empty() || target == "/")
        {
            return "";
        }

        size_t start = (target.front() == '/') ? 1 : 0;
        size_t end = target.find('/', start);

        if (end == std::string_view::npos)
        {
            return std::string(target.substr(start));
        }
        return std::string(target.substr(start, end - start));
    }
}

#endif //HTTP_SERVER_STARTER_CPP_GET_ENDPOINT_HPP
