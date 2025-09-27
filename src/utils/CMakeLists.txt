add_library(utils STATIC
        flag_parser.cpp
        get_endpoint.cpp
)

target_include_directories(utils PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)