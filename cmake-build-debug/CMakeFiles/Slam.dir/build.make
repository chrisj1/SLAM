# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chrisjerrett/Desktop/Slam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chrisjerrett/Desktop/Slam/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Slam.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Slam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Slam.dir/flags.make

CMakeFiles/Slam.dir/main.cpp.o: CMakeFiles/Slam.dir/flags.make
CMakeFiles/Slam.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chrisjerrett/Desktop/Slam/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Slam.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Slam.dir/main.cpp.o -c /Users/chrisjerrett/Desktop/Slam/main.cpp

CMakeFiles/Slam.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Slam.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chrisjerrett/Desktop/Slam/main.cpp > CMakeFiles/Slam.dir/main.cpp.i

CMakeFiles/Slam.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Slam.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chrisjerrett/Desktop/Slam/main.cpp -o CMakeFiles/Slam.dir/main.cpp.s

CMakeFiles/Slam.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Slam.dir/main.cpp.o.requires

CMakeFiles/Slam.dir/main.cpp.o.provides: CMakeFiles/Slam.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Slam.dir/build.make CMakeFiles/Slam.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Slam.dir/main.cpp.o.provides

CMakeFiles/Slam.dir/main.cpp.o.provides.build: CMakeFiles/Slam.dir/main.cpp.o


# Object files for target Slam
Slam_OBJECTS = \
"CMakeFiles/Slam.dir/main.cpp.o"

# External object files for target Slam
Slam_EXTERNAL_OBJECTS =

Slam: CMakeFiles/Slam.dir/main.cpp.o
Slam: CMakeFiles/Slam.dir/build.make
Slam: CMakeFiles/Slam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chrisjerrett/Desktop/Slam/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Slam"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Slam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Slam.dir/build: Slam

.PHONY : CMakeFiles/Slam.dir/build

CMakeFiles/Slam.dir/requires: CMakeFiles/Slam.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Slam.dir/requires

CMakeFiles/Slam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Slam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Slam.dir/clean

CMakeFiles/Slam.dir/depend:
	cd /Users/chrisjerrett/Desktop/Slam/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chrisjerrett/Desktop/Slam /Users/chrisjerrett/Desktop/Slam /Users/chrisjerrett/Desktop/Slam/cmake-build-debug /Users/chrisjerrett/Desktop/Slam/cmake-build-debug /Users/chrisjerrett/Desktop/Slam/cmake-build-debug/CMakeFiles/Slam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Slam.dir/depend

