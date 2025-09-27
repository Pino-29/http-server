//
// Created by Roberto Jesus Garcia Pino on 10/09/25.
//

#include "get/endpoints/files.hpp"

#include "core/config.hpp"
#include "../../../include/core/request/request.hpp"
#include "../../../include/core/response/response.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace http::get::endpoints
{
    namespace fs = std::filesystem;

    http::Response fileNotFound(const Request& request)
    {
        http::Response response(http::StatusCode::NotFound);

        response.setVersion(request.version)
                .addHeader("Content-Type", "text/plain")
                .setBody(std::string_view("The requested resource was not found."));

        return response;
    }

    std::vector<char> readFileContent(const fs::path& path)
    {
        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Failed to open file: " + path.string());
        }

        return {
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()
        };
    }

    http::Response fileRequest(const fs::path& filepath, const Request& request)
    {
        Response response(StatusCode::OK);
        response.setVersion(request.version)
                .addHeader("Content-Type", "application/octet-stream")
                .setBody(readFileContent(filepath));

        return response;
    }

    Response directoryRequest(const fs::path& dirPath, const Request& request)
    {
        std::string dirList {};
        std::cout << "📁 It's a directory: " << dirPath << "\n";

        fs::path indexFile { dirPath / "index.html" };
        if (fs::exists(indexFile))
        {
            std::cout << "📄 Serving index file: " << indexFile << "\n";
            return fileRequest(indexFile, request);
        }

        std::cout << "📂 Listing directory contents:\n";
        for (const auto& entry: fs::directory_iterator(dirPath))
        {
            dirList += " - " + entry.path().filename().string() + "\n";
        }

        Response response(StatusCode::OK);
        response.setVersion(request.version)
                .addHeader("Content-Type", "application/octet-stream")
                .setBody(dirList);
        return response;
    }

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

    http::Response files(const Request& request)
    {
        std::cout << "files\n";
        const fs::path path { getFilePath(request.target) };
        std::cout << "Path: " << path.string() << "\n";

        std::error_code ec;
        bool isDir { std::filesystem::is_directory(path, ec) };
        if (!ec && isDir)
        {
            return directoryRequest(path, request);
        }

        if (fs::is_regular_file(path))
        {
            std::cout << "📄 It's a file: " << path << "\n";
            return fileRequest(path, request);
        }

        return fileNotFound(request);
    }
}
