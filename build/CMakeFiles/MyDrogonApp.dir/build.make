# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/amygdala/cod/drogon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/amygdala/cod/drogon/build

# Include any dependencies generated for this target.
include CMakeFiles/MyDrogonApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyDrogonApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyDrogonApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyDrogonApp.dir/flags.make

CMakeFiles/MyDrogonApp.dir/main.cc.o: CMakeFiles/MyDrogonApp.dir/flags.make
CMakeFiles/MyDrogonApp.dir/main.cc.o: /Users/amygdala/cod/drogon/main.cc
CMakeFiles/MyDrogonApp.dir/main.cc.o: CMakeFiles/MyDrogonApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/amygdala/cod/drogon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyDrogonApp.dir/main.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyDrogonApp.dir/main.cc.o -MF CMakeFiles/MyDrogonApp.dir/main.cc.o.d -o CMakeFiles/MyDrogonApp.dir/main.cc.o -c /Users/amygdala/cod/drogon/main.cc

CMakeFiles/MyDrogonApp.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyDrogonApp.dir/main.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/amygdala/cod/drogon/main.cc > CMakeFiles/MyDrogonApp.dir/main.cc.i

CMakeFiles/MyDrogonApp.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyDrogonApp.dir/main.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/amygdala/cod/drogon/main.cc -o CMakeFiles/MyDrogonApp.dir/main.cc.s

# Object files for target MyDrogonApp
MyDrogonApp_OBJECTS = \
"CMakeFiles/MyDrogonApp.dir/main.cc.o"

# External object files for target MyDrogonApp
MyDrogonApp_EXTERNAL_OBJECTS =

MyDrogonApp: CMakeFiles/MyDrogonApp.dir/main.cc.o
MyDrogonApp: CMakeFiles/MyDrogonApp.dir/build.make
MyDrogonApp: /usr/local/lib/libdrogon.a
MyDrogonApp: /usr/local/lib/libtrantor.a
MyDrogonApp: /opt/homebrew/lib/libssl.dylib
MyDrogonApp: /opt/homebrew/lib/libcrypto.dylib
MyDrogonApp: /opt/homebrew/lib/libjsoncpp.dylib
MyDrogonApp: /Users/amygdala/miniconda3/lib/libyaml-cpp.0.7.0.dylib
MyDrogonApp: /opt/homebrew/lib/libuuid.dylib
MyDrogonApp: /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/usr/lib/libsqlite3.tbd
MyDrogonApp: /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/usr/lib/libz.tbd
MyDrogonApp: CMakeFiles/MyDrogonApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/amygdala/cod/drogon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyDrogonApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyDrogonApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyDrogonApp.dir/build: MyDrogonApp
.PHONY : CMakeFiles/MyDrogonApp.dir/build

CMakeFiles/MyDrogonApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyDrogonApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyDrogonApp.dir/clean

CMakeFiles/MyDrogonApp.dir/depend:
	cd /Users/amygdala/cod/drogon/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/amygdala/cod/drogon /Users/amygdala/cod/drogon /Users/amygdala/cod/drogon/build /Users/amygdala/cod/drogon/build /Users/amygdala/cod/drogon/build/CMakeFiles/MyDrogonApp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyDrogonApp.dir/depend

