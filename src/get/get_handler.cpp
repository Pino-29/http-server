//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#include "get/get_handler.hpp"

#include "get/endpoints/empty.hpp"
#include "get/endpoints/echo.hpp"
#include "get/endpoints/files.hpp"
#include "get/endpoints/user_agent.hpp"
#include "utils/get_endpoint.hpp"

#include <iostream>
#include <string_view>
#include <sys/socket.h>

namespace http::get
{
    GetHandler::GetHandler()
    {
        m_routes[""] = endpoints::empty;
        m_routes["echo"] = endpoints::echo;
        m_routes["user-agent"] = endpoints::userAgent;
        m_routes["files"] = endpoints::files;
    }

    void GetHandler::route(int clientFD, const Request& request) const
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

        std::string responseStr = response.toString();
        send(clientFD, responseStr.c_str(), responseStr.length(), 0);
    }
} // namespace http::get
