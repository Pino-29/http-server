//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#include "core/config.hpp"
#include "parse_body_helper.hpp"
#include "core/request.hpp"

#include <algorithm>
#include <charconv>
#include <iostream>
#include <limits>
#include <sstream>

namespace http
{
    size_t getContentLength(const Request& request)
    {
        if (!request.hasHeader("Content-Length"))
        {
            return 0;
        }

        auto contentLengthStr { request.getHeader("Content-Length") };
        size_t length {};

        auto [ptr, ec] = std::from_chars(
            contentLengthStr.data(),
            contentLengthStr.data() + contentLengthStr.size(),
            length);

        if (ec != std::errc() || ptr != contentLengthStr.data() + contentLengthStr.size())
        {
            throw std::runtime_error("Invalid Content-Length header value");
        }

        return length;
    }

    void parseBodyHelper(Request& request, std::istringstream& iss)
    {
        auto contentLength { getContentLength(request) };
        std::cout << "Content-Length: " << contentLength << "\n";

        if (contentLength == 0)
        {
            return;
        }

        request.body.resize(contentLength);

        if (contentLength > static_cast<size_t>(std::numeric_limits<std::streamsize>::max()))
        {
            throw std::runtime_error("Content-Length is too large to process.");
        }

        iss.read(request.body.data(), static_cast<std::streamsize>(contentLength));

        if (static_cast<size_t>(iss.gcount()) != contentLength)
        {
            throw std::runtime_error("Incomplete message body: stream ended prematurely.");
        }

        for (size_t i = 0; i < contentLength; ++i)
        {
            std::cout << request.body[i];
        }
        std::cout << "\n";
    }
}
