#include "core/config.hpp"
#include "core/server.hpp"
#include "utils/flag_parser.hpp"

#include <iostream>


int main(int argc, char *argv[])
{
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    try
    {
        const std::vector<std::string_view> args(argv + 1, argv + argc);

        Config config = cli::parseFlags(args);
        config.lock();

        int port = 4221;
        if (config.contains("port"))
        {
            port = std::stoi(config.at("port"));
        }

        http::Server({ .port = port, .connectionBacklog = 10 }).run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Critical error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
