cmake_minimum_required(VERSION 3.13)
project(http-server-starter-cpp)

# --- Build Type Configuration ---
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
# --- End of Configuration ---

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)

add_subdirectory(src/core)
add_subdirectory(src/get)
add_subdirectory(src/post)
add_subdirectory(src/utils)

# Define the final executable
add_executable(server src/main.cpp)

target_link_libraries(server PRIVATE
        core
        get
        post
        utils
        Threads::Threads
)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")