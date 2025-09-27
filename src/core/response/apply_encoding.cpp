//
// Created by Roberto Jesus Garcia Pino on 26/09/25.
//

#include "../../../include/core/response/apply_encoding.hpp"

#include "core/request/request.hpp"
#include "core/response/response.hpp"

#include <sstream>

namespace http
{
    void applyEncoding(const Request& request, Response& response)
    {
        std::string acceptedEncodingsStr = request.getHeader("Accept-Encoding");
        if (acceptedEncodingsStr.empty())
        {
            return;
        }

        const std::vector<std::string_view> serverSupportedEncodings = { "gzip" };

        std::stringstream ss(acceptedEncodingsStr);
        std::string encodingToken;

        while (std::getline(ss, encodingToken, ','))
        {
            encodingToken.erase(0, encodingToken.find_first_not_of(" \t"));
            encodingToken.erase(encodingToken.find_last_not_of(" \t") + 1);

            for (const auto& supported: serverSupportedEncodings)
            {
                if (encodingToken == supported)
                {
                    if (supported == "gzip")
                    {
                        response.encode(http::Encoding::GZIP);
                    }
                    return;
                }
            }
        }
    }
}
