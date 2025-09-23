//
// Created by Roberto Jesus Garcia Pino on 23/09/25.
//

#include "utils/flag_parser.hpp"

#include "core/config.hpp"

#include <iostream>


namespace cli
{
    Config parseFlags(const std::vector<std::string_view>& args)
    {
        Config& config { Config::instance() };
        for (size_t i = 0; i < args.size(); ++i)
        {
            if (args[i].starts_with("--"))
            {
                if (i + 1 >= args.size())
                {
                    throw std::runtime_error("Flag " + std::string(args[i]) + " is missing a value.");
                }
                std::string_view key = args[i].substr(2);
                config[std::string(key)] = args[i + 1];
                std::cout << "Flag " << key << " set to " << args[i + 1] << "\n";
                ++i; // Skip the value
            }
        }

        return config;
    }
}
