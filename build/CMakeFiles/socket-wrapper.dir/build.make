# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tal/Desktop/dev/socket-wrapper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tal/Desktop/dev/socket-wrapper/build

# Include any dependencies generated for this target.
include CMakeFiles/socket-wrapper.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/socket-wrapper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/socket-wrapper.dir/flags.make

CMakeFiles/socket-wrapper.dir/src/Socket.cpp.o: CMakeFiles/socket-wrapper.dir/flags.make
CMakeFiles/socket-wrapper.dir/src/Socket.cpp.o: ../src/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tal/Desktop/dev/socket-wrapper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/socket-wrapper.dir/src/Socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socket-wrapper.dir/src/Socket.cpp.o -c /home/tal/Desktop/dev/socket-wrapper/src/Socket.cpp

CMakeFiles/socket-wrapper.dir/src/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socket-wrapper.dir/src/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tal/Desktop/dev/socket-wrapper/src/Socket.cpp > CMakeFiles/socket-wrapper.dir/src/Socket.cpp.i

CMakeFiles/socket-wrapper.dir/src/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socket-wrapper.dir/src/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tal/Desktop/dev/socket-wrapper/src/Socket.cpp -o CMakeFiles/socket-wrapper.dir/src/Socket.cpp.s

# Object files for target socket-wrapper
socket__wrapper_OBJECTS = \
"CMakeFiles/socket-wrapper.dir/src/Socket.cpp.o"

# External object files for target socket-wrapper
socket__wrapper_EXTERNAL_OBJECTS =

libsocket-wrapper.so: CMakeFiles/socket-wrapper.dir/src/Socket.cpp.o
libsocket-wrapper.so: CMakeFiles/socket-wrapper.dir/build.make
libsocket-wrapper.so: CMakeFiles/socket-wrapper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tal/Desktop/dev/socket-wrapper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libsocket-wrapper.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/socket-wrapper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/socket-wrapper.dir/build: libsocket-wrapper.so

.PHONY : CMakeFiles/socket-wrapper.dir/build

CMakeFiles/socket-wrapper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/socket-wrapper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/socket-wrapper.dir/clean

CMakeFiles/socket-wrapper.dir/depend:
	cd /home/tal/Desktop/dev/socket-wrapper/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tal/Desktop/dev/socket-wrapper /home/tal/Desktop/dev/socket-wrapper /home/tal/Desktop/dev/socket-wrapper/build /home/tal/Desktop/dev/socket-wrapper/build /home/tal/Desktop/dev/socket-wrapper/build/CMakeFiles/socket-wrapper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/socket-wrapper.dir/depend

