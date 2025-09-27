//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

// #include "get/endpoints/user_agent.hpp"

#include <iostream>
#include <ostream>

#include "../../../include/core/request/request.hpp"
#include "../../../include/core/response/response.hpp"

#include <string>

namespace http::get::endpoints
{
    Response userAgent(const Request& request)
    {
        const auto body { request.getHeader("User-Agent") };

        Response response(StatusCode::OK);
        response.setVersion(request.version)
                .addHeader("Content-Type", "text/plain")
                .setBody(body);

        return response;
    }
}
