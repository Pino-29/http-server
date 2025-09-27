//
// Created by Roberto Jesus Garcia Pino on 23/09/25.
//

#include "../../../include/core/response/response.hpp"

#include <sstream>
#include <stdexcept>
#include <zlib.h>

namespace http
{
    Response::Response(StatusCode status) : m_status(status)
    {
    }

    Response& Response::setStatusCode(StatusCode status)
    {
        m_status = status;
        return *this;
    }

    Response& Response::setVersion(Version version)
    {
        m_version = version;
        return *this;
    }

    Response& Response::addHeader(std::string_view name, std::string_view value)
    {
        m_headers[std::string(name)] = std::string(value);
        return *this;
    }

    Response& Response::setBody(std::string_view body)
    {
        m_body.assign(body.begin(), body.end());
        return *this;
    }

    Response& Response::setBody(const Buffer& body)
    {
        m_body = body;
        return *this;
    }

    Response& Response::compress(Encoding encoding)
    {
        if (m_body.empty() || m_headers.contains("Content-Encoding"))
        {
            return *this; // Nothing to compress or already compressed
        }

        if (encoding == Encoding::GZIP)
        {
            z_stream zs = {};
            if (deflateInit2(&zs, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY) != Z_OK)
            {
                throw std::runtime_error("deflateInit2 failed while compressing.");
            }

            zs.next_in = reinterpret_cast<Bytef *>(m_body.data());
            zs.avail_in = m_body.size();

            Buffer compressed_body;
            compressed_body.resize(compressBound(m_body.size()));

            zs.next_out = reinterpret_cast<Bytef *>(compressed_body.data());
            zs.avail_out = compressed_body.size();

            deflate(&zs, Z_FINISH);
            deflateEnd(&zs);

            compressed_body.resize(zs.total_out);
            m_body = std::move(compressed_body);
            addHeader("Content-Encoding", "gzip");
        }
        return *this;
    }

    std::string Response::toString() const
    {
        std::ostringstream response_stream;

        // Status Line
        response_stream << "HTTP/1.1" << " " << static_cast<int>(m_status) << " " << getReasonPhrase() << "\r\n";

        // Add Content-Length now that the body is finalized
        response_stream << "Content-Length: " << m_body.size() << "\r\n";

        // Add other headers
        for (const auto& [name, value]: m_headers)
        {
            response_stream << name << ": " << value << "\r\n";
        }

        // End of headers
        response_stream << "\r\n";

        // Add the body (if any)
        if (!m_body.empty())
        {
            response_stream.write(m_body.data(), m_body.size());
        }

        return response_stream.str();
    }

    std::string_view Response::getReasonPhrase() const
    {
        switch (m_status)
        {
            case StatusCode::OK: return "OK";
            case StatusCode::Created: return "Created";
            case StatusCode::BadRequest: return "Bad Request";
            case StatusCode::NotFound: return "Not Found";
            case StatusCode::InternalServerError: return "Internal Server Error";
            case StatusCode::NotImplemented: return "Not Implemented";
            default: return "Unknown";
        }
    }
} // namespace http
