cmake_minimum_required(VERSION 3.27)
project(simple_analytics)
set(CMAKE_OSX_ARCHITECTURES arm64)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# Make sure to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(CURL REQUIRED)

include(FetchContent)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.12.0  
)

# Make the fetched content available
FetchContent_MakeAvailable(spdlog)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define the main executable
add_executable(pxli 
    pxli.cc
)

target_link_libraries(
  pxli PRIVATE 
  spdlog 
  curl
)


