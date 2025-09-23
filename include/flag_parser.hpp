//
// Created by Roberto Jesus Garcia Pino on 23/09/25.
//

#ifndef HTTP_SERVER_STARTER_CPP_FLAG_PARSER_HPP
#define HTTP_SERVER_STARTER_CPP_FLAG_PARSER_HPP

#include "core/config.hpp"

#include <vector>
#include <string_view>

namespace cli
{
    /**
     * @brief Parses command-line arguments into a key-value map.
     * @param args The command-line arguments.
     * @return A map containing the parsed configuration.
     * @throws std::runtime_error if a flag is missing its value.
     */
    Config parseFlags(const std::vector<std::string_view>& args);
}

#endif //HTTP_SERVER_STARTER_CPP_FLAG_PARSER_HPP
