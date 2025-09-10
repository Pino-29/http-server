//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#include "http_request.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>


namespace http
{
    std::string toString(const Method& method)
    {
        switch (method) {
            case Method::GET:     return "GET";
            case Method::POST:    return "POST";
            case Method::PUT:     return "PUT";
            case Method::DELETE:  return "DELETE";
            case Method::HEAD:    return "HEAD";
            case Method::OPTIONS: return "OPTIONS";
            case Method::TRACE:   return "TRACE";
            case Method::CONNECT: return "CONNECT";
            case Method::PATCH:   return "PATCH";
            default:              return "UNKNOWN";
        }
    }

    std::string toString(const Version& version)
    {
        switch (version)
        {
            case Version::HTTP_1_0: return "HTTP/1.0";
            case Version::HTTP_1_1: return "HTTP/1.1";
            case Version::HTTP_2:   return "HTTP/2";
            case Version::HTTP_3:   return "HTTP/3";
            default:                return "UNKNOWN";
        }
    }

    std::ostream& operator<<(std::ostream& os, const Method& method) {
        return os << toString(method);
    }

    std::ostream& operator<<(std::ostream& os, const Version& version)
    {
        return os << toString(version);
    }

    Method parseMethod(const std::string& methodStr) {
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

    Version parseVersion(const std::string& versionStr)
    {
        if (versionStr == "HTTP/1.0") return Version::HTTP_1_0;
        if (versionStr == "HTTP/1.1") return Version::HTTP_1_1;
        if (versionStr == "HTTP/2") return Version::HTTP_2;
        if (versionStr == "HTTP/3") return Version::HTTP_3;
        throw std::invalid_argument("Unknown HTTP version: " + versionStr);
    }

    [[nodiscard]] bool isCRLFNext(std::istringstream& iss)
    {
        char first{}, second{};
        if (iss.get(first) && iss.get(second)) {
            if (first != '\r' || second != '\n') {
                std::cerr << "Unexpected line ending: '" << first << " " << second << "\n";
                return false;
            }
        } else {
            throw std::invalid_argument("Invalid request line: stream failed before \\r\\n");
        }

        return true;
    }

    void parseLineHelper(Request& parseRequest, std::istringstream& iss)
    {
        std::string method;
        if (iss >> method) {
            try {
                parseRequest.method = parseMethod(method);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\nFailed to parse method\n";
                throw;
            }
        } else {
            std::cerr << "Error: Failed to extract method from stream\n";
            throw std::runtime_error("Stream extraction failed for HTTP method");
        }
        std::cout << "Method: " << parseRequest.method << "\n";

        std::string target;
        if (iss >> target) {
            parseRequest.target = std::move(target);
        } else {
            std::cerr << "Error: Failed to extract target from stream\n";
            throw std::runtime_error("Stream extraction failed for HTTP target");
        }
        std::cout << "Target: " << parseRequest.target << "\n";

        std::string version;
        if (iss >> version) {
            try {
                parseRequest.version = parseVersion(version);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\nFailed to parse version\n";
                throw;
            }
        } else {
            std::cerr << "Error: Failed to extract version from stream\n";
            throw std::runtime_error("Stream extraction failed for HTTP version");
        }
        std::cout << "Version: " << parseRequest.version << "\n";

        if (!isCRLFNext(iss)) {
            throw std::runtime_error("Failed to read CRLF");
        }
    }

    Request parseRequest(const std::string& request)
    {
        Request parsedRequest{};

        std::istringstream iss { request };
        parseLineHelper(parsedRequest, iss);
        // TODO
        // parse headers and body

        return parsedRequest;
    }
}
