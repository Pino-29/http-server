add_library(core STATIC
        config.cpp
        connection_handler.cpp
        request/request.cpp
        request/request_parser.cpp
        server.cpp
        sockets/socket_setup.cpp
        response/apply_encoding.cpp
        response/response.cpp
)

target_include_directories(core PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(core PRIVATE ZLIB::ZLIB)