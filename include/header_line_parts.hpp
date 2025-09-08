//
// Created by Roberto Jesus Garcia Pino on 08/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_HEADER_LINE_PARTS_H
#define HTTP_SERVER_STARTER_CPP_HEADER_LINE_PARTS_H

enum class RequestLineParts : size_t
{
    kMethod = 0,
    kTarget,
    kVersion,
};

#endif //HTTP_SERVER_STARTER_CPP_HEADER_LINE_PARTS_H