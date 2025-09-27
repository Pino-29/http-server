//
// Created by Roberto Jesus Garcia Pino on 25/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_HANDLERS_HPP
#define HTTP_SERVER_STARTER_CPP_HANDLERS_HPP

#include "get/get_handler.hpp"
#include "post/post_handler.hpp"

namespace http
{
    inline const get::GetHandler& getHandlerInstance()
    {
        static const get::GetHandler getHandler;
        return getHandler;
    }

    inline const post::PostHandler& postHandlerInstance()
    {
        static const post::PostHandler postHandler;
        return postHandler;
    }
}


#endif //HTTP_SERVER_STARTER_CPP_HANDLERS_HPP
