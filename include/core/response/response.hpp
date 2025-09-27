//
// Created by Roberto Jesus Garcia Pino on 23/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_RESPONSE_HPP
#define HTTP_SERVER_STARTER_CPP_RESPONSE_HPP

#include "core/http_types.hpp"
#include "core/types.hpp"
#include <string>
#include <string_view>
#include <unordered_map>

namespace http
{
    enum class Encoding
    {
        GZIP
    };

    class Response
    {
    public:
        explicit Response(StatusCode status = StatusCode::OK);

        Response& setStatusCode(StatusCode status);

        Response& setVersion(Version version);

        Response& addHeader(std::string_view name, std::string_view value);

        Response& setBody(std::string_view body);

        Response& setBody(const Buffer& body);

        Response& compress(Encoding encoding);

        [[nodiscard]] std::string toString() const;

    private:
        Version m_version { Version::HTTP_1_1 };
        StatusCode m_status {};
        std::unordered_map<std::string, std::string> m_headers {};
        Buffer m_body {};

        // Helper to get the reason phrase for a status code
        [[nodiscard]] std::string_view getReasonPhrase() const;
    };
} // http

#endif //HTTP_SERVER_STARTER_CPP_RESPONSE_HPP
