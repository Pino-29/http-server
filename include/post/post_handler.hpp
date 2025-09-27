//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_POST_H
#define HTTP_SERVER_STARTER_CPP_POST_H

#include "../core/request/request.hpp"
#include "core/response/response.hpp"

namespace http::post
{
    using EndpointHandler = Response(*)(const Request&);

    class PostHandler
    {
    public:
        PostHandler();

        explicit PostHandler(const EndpointHandler& handler);

        void route(int clientFD, const Request& request) const;

    private:
        std::unordered_map<std::string, EndpointHandler> m_routes;
    };
} // namespace http::get

#endif //HTTP_SERVER_STARTER_CPP_POST_H
