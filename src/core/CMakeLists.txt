add_library(core STATIC
        config.cpp
        connection_handler.cpp
        request.cpp
        request_parser.cpp
        server.cpp
        socket_setup.cpp
)

target_include_directories(core PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)