//
// Created by Roberto Jesus Garcia Pino on 09/09/25.
//

#ifndef GET_HANDLER_HPP
#define GET_HANDLER_HPP

#include "core/request/request.hpp"
#include "core/response/response.hpp"

#include <functional>
#include <string>
#include <unordered_map>

namespace http::get
{
    using EndpointHandler = Response(*)(const Request&);

    class GetHandler
    {
    public:
        GetHandler();

        Response route(const Request& request) const;

    private:
        std::unordered_map<std::string, EndpointHandler> m_routes;
    };
} // namespace http::get

#endif // GET_HANDLER_HPP
