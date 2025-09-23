//
// Created by Roberto Jesus Garcia Pino on 08/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_HTTP_REQUEST_H
#define HTTP_SERVER_STARTER_CPP_HTTP_REQUEST_H
#include <vector>
#include <unordered_map>
#include <string>

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

    struct Request
    {
        Method method {};
        std::string target {};
        Version version {};

        // Headers: key-value pairs
        std::unordered_map<std::string, std::string> headers {};

        // Optional body (for POST, PUT, PATCH, etc.)
        std::vector<char> body {};

        // Optional query parameters (parsed from URI)
        std::unordered_map<std::string, std::string> queryParams {};

        // Utility: Check if a header exists
        [[nodiscard]] bool hasHeader(const std::string& key) const
        {
            return headers.find(key) != headers.end();
        }

        // Utility: Get header value with fallback
        [[nodiscard]] std::string getHeader(const std::string& key, const std::string& defaultValue = "") const
        {
            auto it = headers.find(key);
            return it != headers.end() ? it->second : defaultValue;
        }

        // Utility: Get query param with fallback
        [[nodiscard]] std::string getQueryParam(const std::string& key, const std::string& defaultValue = "") const
        {
            auto it = queryParams.find(key);
            return it != queryParams.end() ? it->second : defaultValue;
        }
    };

    std::string toString(const Method& method);

    std::string toString(const Version& version);

    std::ostream& operator<<(std::ostream& os, const Method& method);

    std::ostream& operator<<(std::ostream& os, const Version& version);
}

#endif // HTTP_SERVER_STARTER_CPP_HTTP_REQUEST_H
