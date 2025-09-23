//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_REQUEST_PARSER_HPP
#define HTTP_SERVER_STARTER_CPP_REQUEST_PARSER_HPP

#include "core/request.hpp"
#include "core/types.hpp"

#include <sstream>

namespace http
{
    class RequestParser
    {
    public:
        explicit RequestParser(const Buffer& buffer);

        [[nodiscard]] Request parse();

    private:
        // Private state for the parser
        Request m_request;
        std::istringstream m_iss;

        void parseRequestLine();

        void parseHeaders();

        void parseBody();

        static Method parseMethod(const std::string& methodStr);

        static Version parseVersion(const std::string& versionStr);

        static void trim(std::string& s);
    };
}

#endif //HTTP_SERVER_STARTER_CPP_REQUEST_PARSER_HPP
