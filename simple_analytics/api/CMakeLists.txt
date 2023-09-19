# Specify the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(Cserv C)

# Add the directory where your source files are located
# (Assuming they are all in a 'src' directory)
aux_source_directory(src SOURCE_FILES)

# Find the required libevent package
find_package(Libevent REQUIRED)

# Specify the executable and its source files
add_executable(my_app ${SOURCE_FILES})

# Link the executable with the libevent library
target_link_libraries(cserv PRIVATE Libevent::Libevent)

# Specify any required compiler flags, if needed
# For example, for C11 support:
# set_property(TARGET my_app PROPERTY C_STANDARD 11)

# Installation rules, if you want to install the binary somewhere
# install(TARGETS my_app DESTINATION bin)

