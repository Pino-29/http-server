//
// Created by Roberto Jesus Garcia Pino on 23/09/25.
//

#include "../../../include/core/response/response.hpp"

#include <iostream>
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

    Response& Response::encode(Encoding encoding)
    {
        if (m_body.empty() || m_headers.contains("Content-Encoding"))
        {
            return *this;
        }

        if (encoding == Encoding::GZIP)
        {
            z_stream zs = {};
            if (deflateInit2(&zs, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY) != Z_OK)
            {
                throw std::runtime_error("deflateInit2 failed while encoding.");
            }

            zs.next_in = reinterpret_cast<Bytef *>(m_body.data());
            zs.avail_in = m_body.size();

            int ret;
            char out_buffer[32768]; // A temporary 32KB chunk buffer
            Buffer encoded_body;

            do
            {
                zs.next_out = reinterpret_cast<Bytef *>(out_buffer);
                zs.avail_out = sizeof(out_buffer);

                ret = deflate(&zs, Z_FINISH);

                if (encoded_body.size() < zs.total_out)
                {
                    encoded_body.insert(encoded_body.end(), out_buffer,
                                        out_buffer + (sizeof(out_buffer) - zs.avail_out));
                }
            } while (ret == Z_OK);

            deflateEnd(&zs);

            if (ret != Z_STREAM_END)
            {
                throw std::runtime_error("Compression failed with zlib error code: " + std::to_string(ret));
            }

            m_body = std::move(encoded_body);
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
