//
// Created by Roberto Jesus Garcia Pino on 23/09/25.
//

#include "../../../include/get/endpoints/empty.hpp"

#include "../../../include/core/http_types.hpp"
#include "../../../include/core/request/request.hpp"
#include "../../../include/core/response/response.hpp"

namespace http::get::endpoints
{
    /**
     * @brief Creates a simple 200 OK response with an empty body.
     * @param request The incoming client request.
     * @return A configured Response object.
     */
    Response empty(const Request& request)
    {
        Response response(StatusCode::OK);

        response.setVersion(request.version)
                .setBody(std::string_view(""));

        return response;
    }
}