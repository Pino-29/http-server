//
// Created by Roberto Jesus Garcia Pino on 08/09/25.
//

#include "get/endpoints/echo.hpp"

#include "../../../include/core/request/request.hpp"
#include "../../../include/core/response/response.hpp"
#include "../../../include/get/endpoints/empty.hpp"

#include <ostream>
#include <string>

namespace http::get::endpoints
{
    Response echo(const Request& request)
    {
        std::string_view echoString = request.target;
        constexpr std::string_view prefix { "/echo/" };
        if (!echoString.starts_with(prefix) || echoString.size() == prefix.size())
        {
            return empty(request);
        }

        echoString.remove_prefix(prefix.size());
        Response response(StatusCode::OK);
        response.setVersion(request.version)
                .addHeader("Content-Type", "text/plain")
                .setBody(echoString);
        return response;
    }
}
