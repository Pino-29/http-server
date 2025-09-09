//
// Created by Roberto Jesus Garcia Pino on 08/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_HEADER_LINE_PARTS_H
#define HTTP_SERVER_STARTER_CPP_HEADER_LINE_PARTS_H
#include <vector>

namespace http
{
    enum class Method : size_t
    {
        GET,
        POST,
        PUT,
        DELETE,
        HEAD,
        OPTIONS,
        TRACE,
        CONNECT,
        PATCH
    };

    inline Method parseMethod(const std::string& methodStr) {
        if (methodStr == "GET") return Method::GET;
        if (methodStr == "POST") return Method::POST;
        if (methodStr == "PUT") return Method::PUT;
        if (methodStr == "DELETE") return Method::DELETE;
        if (methodStr == "HEAD") return Method::HEAD;
        if (methodStr == "OPTIONS") return Method::OPTIONS;
        if (methodStr == "TRACE") return Method::TRACE;
        if (methodStr == "CONNECT") return Method::CONNECT;
        if (methodStr == "PATCH") return Method::PATCH;

        throw std::invalid_argument("Unknown HTTP method: " + methodStr);
    }

    enum class Version : size_t
    {
        HTTP_1_0,
        HTTP_1_1,
        HTTP_2,
        HTTP_3
    };

    inline Version parseVersion(const std::string& versionStr)
    {
        if (versionStr == "HTTP/1.0") return Version::HTTP_1_0;
        if (versionStr == "HTTP/1.1") return Version::HTTP_1_1;
        if (versionStr == "HTTP/2") return Version::HTTP_2;
        if (versionStr == "HTTP/3") return Version::HTTP_3;
        throw std::invalid_argument("Unknown HTTP version: " + versionStr);
    }

    struct RequestLine
    {
        Method method{};
        std::string target{};
        Version version{};
    };
}
#endif //HTTP_SERVER_STARTER_CPP_HEADER_LINE_PARTS_H
