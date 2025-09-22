add_library(core STATIC
        config.cpp
        parse_body_helper.cpp
        request.cpp
)

target_include_directories(core PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)