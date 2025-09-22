//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_PARSE_BODY_HELPER_H
#define HTTP_SERVER_STARTER_CPP_PARSE_BODY_HELPER_H

#include "request.hpp"

#include <sstream>

namespace http
{
    void parseBodyHelper(Request& request, std::istringstream& iss);
}

#endif //HTTP_SERVER_STARTER_CPP_PARSE_BODY_HELPER_H