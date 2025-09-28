//
// Created by Roberto Jesus Garcia Pino on 23/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_HTTP_TYPES_HPP
#define HTTP_SERVER_STARTER_CPP_HTTP_TYPES_HPP

#include <cstddef>

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

    enum class Version : size_t
    {
        HTTP_1_0,
        HTTP_1_1,
        HTTP_2,
        HTTP_3
    };

    enum class StatusCode : int
    {
        OK = 200,
        Created = 201,
        BadRequest = 400,
        NotFound = 404,
        InternalServerError = 500,
        NotImplemented = 501
    };
} // namespace http

#endif //HTTP_SERVER_STARTER_CPP_HTTP_TYPES_HPP