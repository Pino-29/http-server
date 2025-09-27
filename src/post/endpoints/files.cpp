//
// Created by Roberto Jesus Garcia Pino on 20/09/25.
//

#include "post/endpoints/files.hpp"

#include "core/config.hpp"
#include "../../../include/core/request/request.hpp"
#include "core/response/response.hpp"

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

    Response badRequest(const Request& request, std::string_view message)
    {
        Response response(StatusCode::BadRequest);
        response.setVersion(request.version)
                .addHeader("Content-Type", "text/plain")
                .setBody(message);
        return response;
    }


    Response goodRequest(const fs::path& path, const Request& request)
    {
        http::Response response;
        response.setVersion(request.version);

        std::ofstream outFile(path, std::ios::binary);
        if (!outFile)
        {
            std::string_view message = "Internal Server Error: Could not open file for writing.";

            response.setStatusCode(StatusCode::InternalServerError)
                    .addHeader("Content-Type", "text/plain")
                    .setBody(message);

            return response;
        }

        std::cout << "Writing to file: " << path.string() << "\n";
        outFile.write(request.body.data(), static_cast<std::streamsize>(request.body.size()));
        outFile.close();

        response.setStatusCode(StatusCode::Created);

        return response;
    }

    bool isDirectoryPath(const fs::path& path)
    {
        std::string_view filename { path.filename().string() };
        return filename.empty() || filename == "." || filename == "..";
    }

    Response files(const Request& request)
    {
        std::cout << "files\n";
        const fs::path path { getFilePath(request.target) };
        std::cout << "Path: " << path.string() << "\n";

        if (isDirectoryPath(path))
        {
            return badRequest(request, "Target path cannot be a directory");
        }

        if (fs::exists(path))
        {
            return badRequest(request, "File already exists");
        }

        return goodRequest(path, request);
    }
}
