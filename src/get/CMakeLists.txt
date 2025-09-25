add_library(get STATIC
        get_handler.cpp
        endpoints/echo.cpp
        endpoints/files.cpp
        endpoints/user_agent.cpp
        endpoints/empty.cpp
        ../../include/get/endpoints/empty.hpp
)

target_include_directories(get PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(get PRIVATE core)