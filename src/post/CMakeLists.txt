add_library(post STATIC
        post_handler.cpp
        endpoints/files.cpp
)

target_include_directories(post PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(post PRIVATE core)