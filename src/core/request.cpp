//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#include "core/request.hpp"

#include <iostream>
#include <string>

namespace http
{
    std::string toString(const Method& method)
    {
        switch (method)
        {
            case Method::GET: return "GET";
            case Method::POST: return "POST";
            case Method::PUT: return "PUT";
            case Method::DELETE: return "DELETE";
            case Method::HEAD: return "HEAD";
            case Method::OPTIONS: return "OPTIONS";
            case Method::TRACE: return "TRACE";
            case Method::CONNECT: return "CONNECT";
            case Method::PATCH: return "PATCH";
            default: return "UNKNOWN";
        }
    }

    std::string toString(const Version& version)
    {
        switch (version)
        {
            case Version::HTTP_1_0: return "HTTP/1.0";
            case Version::HTTP_1_1: return "HTTP/1.1";
            case Version::HTTP_2: return "HTTP/2";
            case Version::HTTP_3: return "HTTP/3";
            default: return "UNKNOWN";
        }
    }

    std::ostream& operator<<(std::ostream& os, const Method& method)
    {
        return os << toString(method);
    }

    std::ostream& operator<<(std::ostream& os, const Version& version)
    {
        return os << toString(version);
    }
}
