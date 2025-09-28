//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#include "post/post_handler.hpp"

#include "core/response/apply_encoding.hpp"
#include "../../include/core/request/request.hpp"
#include "post/endpoints/files.hpp"
#include "utils/get_endpoint.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace http::post
{
    PostHandler::PostHandler()
    {
        m_routes["files"] = endpoints::files;
    }

    Response PostHandler::route(const Request& request) const
    {
        std::string endpoint = http::getEndpoint(request.target);

        Response response;
        auto it = m_routes.find(endpoint);
        if (it != m_routes.end())
        {
            const EndpointHandler& handler = it->second;
            response = handler(request);
        }
        else
        {
            response = Response(StatusCode::NotFound);
        }

        applyEncoding(request, response);
        return response;
    }
}
