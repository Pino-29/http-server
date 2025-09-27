//
// Created by Roberto Jesus Garcia Pino on 22/09/25.
//

#include "../../../include/core/request/request_parser.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace http
{
    RequestParser::RequestParser(const Buffer& buffer)
        : m_iss(std::string(buffer.begin(), buffer.end()))
    {
    }

    Request RequestParser::parse()
    {
        parseRequestLine();
        parseHeaders();
        parseBody();
        return m_request;
    }

    void RequestParser::parseRequestLine()
    {
        std::string methodStr, target, versionStr;

        if (!(m_iss >> methodStr >> target >> versionStr))
        {
            throw std::runtime_error("Malformed request line");
        }

        m_request.method = parseMethod(methodStr);
        m_request.target = std::move(target);
        m_request.version = parseVersion(versionStr);

        // Consume the trailing CRLF
        if (m_iss.get() != '\r' || m_iss.get() != '\n')
        {
            throw std::runtime_error("Request line must end with CRLF");
        }
    }

    void RequestParser::parseHeaders()
    {
        std::string line;
        while (std::getline(m_iss, line) && !line.empty())
        {
            if (!line.empty() && line.back() == '\r')
            {
                line.pop_back();
            }

            if (line.empty())
            {
                // End of headers
                break;
            }

            const auto colonPos = line.find(':');
            if (colonPos == std::string::npos)
            {
                throw std::runtime_error("Malformed header (missing colon)");
            }

            std::string name = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);

            trim(name);
            trim(value);
            m_request.headers[name] = value;
        }
    }

    void RequestParser::parseBody()
    {
        if (m_request.headers.contains("Content-Length"))
        {
            try
            {
                int length = std::stoi(m_request.headers.at("Content-Length"));
                m_request.body.resize(length);
                m_iss.read(m_request.body.data(), length);
            }
            catch (const std::exception& e)
            {
                throw std::runtime_error("Invalid Content-Length header");
            }
        }
    }

    Method RequestParser::parseMethod(const std::string& methodStr)
    {
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

    Version RequestParser::parseVersion(const std::string& versionStr)
    {
        if (versionStr == "HTTP/1.0") return Version::HTTP_1_0;
        if (versionStr == "HTTP/1.1") return Version::HTTP_1_1;
        if (versionStr == "HTTP/2") return Version::HTTP_2;
        if (versionStr == "HTTP/3") return Version::HTTP_3;
        throw std::invalid_argument("Unknown HTTP version: " + versionStr);
    }

    void RequestParser::trim(std::string& s)
    {
        s.erase(s.begin(), std::ranges::find_if(s, [](unsigned char ch)
        {
            return !std::isspace(ch);
        }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }).base(), s.end());
    }
}