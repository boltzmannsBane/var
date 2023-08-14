cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyDrogonProject VERSION 1.0)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Drogon package (assuming it provides CMake integration)
find_package(Drogon CONFIG REQUIRED)

# Add the executable
add_executable(MyDrogonApp main.cc)

# Link Drogon libraries to the executable
target_link_libraries(MyDrogonApp PRIVATE Drogon::Drogon)

