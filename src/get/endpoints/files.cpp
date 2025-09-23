//
// Created by Roberto Jesus Garcia Pino on 10/09/25.
//

#include "get/endpoints/files.hpp"

#include "core/config.hpp"
#include "../../../include/core/request/request.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace http::get::endpoints
{
    namespace fs = std::filesystem;

    std::string fileNotFound()
    {
        return "HTTP/1.1 404 Not Found\r\n\r\n";
    }

    std::string readFileContent(const fs::path& path)
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

    std::string fileRequest(const fs::path& filepath)
    {
        std::string response {};
        // status line
        response += "HTTP/1.1 200 OK\r\n";
        // headers
        response += "Content-Type: application/octet-stream\r\n";
        response += "Content-Length: " + std::to_string(fs::file_size(filepath)) + "\r\n";
        response += "\r\n";
        // body
        response += readFileContent(filepath);
        return response;
    }

    std::string directoryRequest(const fs::path& dirPath)
    {
        std::string dirList {};
        std::cout << "📁 It's a directory: " << dirPath << "\n";

        // Option 1: Serve index.html if it exists
        fs::path indexFile { dirPath / "index.html" };
        if (fs::exists(indexFile))
        {
            std::cout << "📄 Serving index file: " << indexFile << "\n";
            return fileRequest(indexFile);
        }


        std::cout << "📂 Listing directory contents:\n";
        for (const auto& entry: fs::directory_iterator(dirPath))
        {
            dirList += " - " + entry.path().filename().string() + "\n";
        }

        std::string response {};
        // status line
        response += "HTTP/1.1 200 OK\r\n";
        // headers
        response += "Content-Type: application/octet-stream\r\n";
        response += "Content-Length: " + std::to_string(dirList.size()) + "\r\n";
        response += "\r\n";
        // body
        response += dirList;

        std::cout << "Response: " << response << "\n";
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

    std::string files(const Request& request)
    {
        std::cout << "files\n";
        const fs::path path { getFilePath(request.target) };
        std::cout << "Path: " << path.string() << "\n";

        std::error_code ec;
        bool isDir { std::filesystem::is_directory(path, ec) };
        if (!ec && isDir)
        {
            return directoryRequest(path);
        }

        if (fs::is_regular_file(path))
        {
            std::cout << "📄 It's a file: " << path << "\n";
            // Serve file content
            return fileRequest(path);
        }

        return fileNotFound();
    }
}
