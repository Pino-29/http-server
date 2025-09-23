//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#include "post/endpoints/files.hpp"

#include "core/config.hpp"
#include "../../../include/core/request/request.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace http::post::endpoints
{
    namespace fs = std::filesystem;

    fs::path getFilePath(std::string_view target)
    {
        constexpr std::string_view prefix { "/files/" };

        if (!target.starts_with(prefix))
        {
            throw std::invalid_argument("Target path must start with /files/");
        }

        std::string_view filename { target.substr(prefix.size()) };
        fs::path dirPath { Config::instance().get("directory") };
        return dirPath / fs::path(filename);
    }

    std::string badRequest(std::string_view message)
    {
        std::ostringstream response;
        response << "HTTP/1.1 400 Bad Request\r\n"
                << "Content-Type: text/plain\r\n"
                << "Content-Length: " << message.length() << "\r\n"
                << "\r\n"
                << message;
        return response.str();
    }


    std::string goodRequest(const fs::path& path, const Request& request)
    {
        std::ofstream outFile(path, std::ios::binary);

        if (!outFile)
        {
            std::string_view message = "Internal Server Error: Could not open file for writing.";
            std::ostringstream response;
            response << "HTTP/1.1 500 Internal Server Error\r\n"
                    << "Content-Type: text/plain\r\n"
                    << "Content-Length: " << message.length() << "\r\n"
                    << "\r\n"
                    << message;
            return response.str();
        }

        std::cout << "Writing to file: " << path.string() << "\n";
        outFile.write(request.body.data(), static_cast<std::streamsize>(request.body.size()));
        outFile.close();

        std::ostringstream response;
        response << "HTTP/1.1 201 Created\r\n"
                << "\r\n";

        return response.str();
    }

    bool isDirectoryPath(const fs::path& path)
    {
        std::string_view filename { path.filename().string() };
        return filename.empty() || filename == "." || filename == "..";
    }

    std::string files(const Request& request)
    {
        std::cout << "files\n";
        const fs::path path { getFilePath(request.target) };
        std::cout << "Path: " << path.string() << "\n";

        if (isDirectoryPath(path))
        {
            return badRequest("Target path cannot be a directory");
        }

        if (fs::exists(path))
        {
            return badRequest("File already exists");
        }

        return goodRequest(path, request);
    }
}
