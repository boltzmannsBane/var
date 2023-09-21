cmake_minimum_required(VERSION 3.14)
project(simple_analytics)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

# libevent
FetchContent_Declare(
  libevent
  GIT_REPOSITORY https://github.com/libevent/libevent.git
  GIT_TAG        release-2.1.12-stable  # Adjust this if you need a different version
)

# spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.12.0  # Adjust this if you need a different version
)

FetchContent_MakeAvailable(googletest libevent spdlog)

# ... [previous CMake code to fetch dependencies] ...

# Configure and build libevent
FetchContent_GetProperties(libevent)
if(NOT libevent_POPULATED)
  FetchContent_Populate(libevent)
  add_subdirectory(${libevent_SOURCE_DIR} ${libevent_BINARY_DIR})
endif()

# Compile the spdlog wrapper
add_library(spdlog_wrapper OBJECT wrappers/spdlog/spdlog_wrapper.cpp)
target_include_directories(spdlog_wrapper PRIVATE ${spdlog_SOURCE_DIR}/include)
set_target_properties(spdlog_wrapper PROPERTIES CXX_STANDARD 20)

# Compile the server.c code
add_library(server_obj OBJECT server.c)
target_include_directories(server_obj PRIVATE 
  ${libevent_SOURCE_DIR}/include 
  ${libevent_BINARY_DIR}/include)

# Link everything together
add_executable(server $<TARGET_OBJECTS:server_obj> $<TARGET_OBJECTS:spdlog_wrapper>)
target_link_libraries(server event event_core event_extra ${CMAKE_DL_LIBS} spdlog::spdlog)

add_subdirectory(tests)
