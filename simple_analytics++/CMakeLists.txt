cmake_minimum_required(VERSION 3.27)
project(simple_analytics)
set(CMAKE_OSX_ARCHITECTURES arm64)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# Make sure to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Fetch Drogon
FetchContent_Declare(
  drogon
  GIT_REPOSITORY https://github.com/an-tao/drogon.git
  GIT_TAG        v1.8.4 
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
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        v2.4.11  
)

# Make the fetched content available
FetchContent_MakeAvailable(spdlog doctest drogon)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/internal)

# Define the main executable
add_executable(simple_analytics src/main.cc internal/handlers/handler.cc)

# Link the main executable to the necessary libraries
target_link_libraries(simple_analytics PRIVATE drogon spdlog)

# Define the test executable
add_executable(simple_analytics_tests tests/test.cc internal/handlers/handler.cc)

# Link the test executable to its dependencies (doctest is primarily header-only, but linking is still a good practice in case that changes)
target_link_libraries(simple_analytics_tests PRIVATE drogon spdlog doctest::doctest)
