cmake_minimum_required(VERSION 3.14)
project(simple_analytics)

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

# GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make the fetched content available
FetchContent_MakeAvailable(drogon spdlog googletest)

# Include directories for your main project
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(handlers STATIC include/handlers/handler.cc)
target_link_libraries(handlers PRIVATE spdlog::spdlog drogon)

# Create the main executable
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cc)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE drogon spdlog::spdlog handlers)

# For tests
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cc)
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_tests PRIVATE drogon gtest gtest_main gmock handlers)

