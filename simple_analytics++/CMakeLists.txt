cmake_minimum_required(VERSION 3.27)
project(simple_analytics)
set(CMAKE_OSX_ARCHITECTURES arm64)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# Make sure to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# libevent
FetchContent_Declare(
  libevent
  GIT_REPOSITORY https://github.com/libevent/libevent.git
  GIT_TAG        release-2.1.12-stable 
)

# spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.12.0  
)

# doctest
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG        v2.4.11  
)

# Make the fetched content available
FetchContent_MakeAvailable(spdlog doctest libevent)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# server lib
add_library(server_lib
    src/startup.cc 
    src/configuration.cc 
    src/telemetry.cc
)
target_link_libraries(server_lib PRIVATE event spdlog routes_lib)

# routes lib
add_library(routes_lib
    src/routes/ping.cc  
    src/routes/hello.cc 
)

target_link_libraries(routes_lib PRIVATE event spdlog)

# Define the main executable
add_executable(server 
    src/main.cc
)

# Link the main executable to the necessary libraries
target_link_libraries(server PRIVATE server_lib event spdlog)

# Define the test executable
add_executable(tests 
    tests/ping.cc 
    tests/hello.cc
)

# Link the test executable to its dependencies 
target_link_libraries(tests PRIVATE server_lib event spdlog doctest::doctest)
