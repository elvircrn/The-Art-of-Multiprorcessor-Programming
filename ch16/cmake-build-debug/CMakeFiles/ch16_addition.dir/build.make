# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/ch16_addition.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ch16_addition.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ch16_addition.dir/flags.make

CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.o: CMakeFiles/ch16_addition.dir/flags.make
CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.o: ../examples/matrix_addition/addition_pool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.o"
	/usr/local/opt/llvm/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.o -c "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/examples/matrix_addition/addition_pool.cpp"

CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.i"
	/usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/examples/matrix_addition/addition_pool.cpp" > CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.i

CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.s"
	/usr/local/opt/llvm/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/examples/matrix_addition/addition_pool.cpp" -o CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.s

# Object files for target ch16_addition
ch16_addition_OBJECTS = \
"CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.o"

# External object files for target ch16_addition
ch16_addition_EXTERNAL_OBJECTS =

ch16_addition: CMakeFiles/ch16_addition.dir/examples/matrix_addition/addition_pool.cpp.o
ch16_addition: CMakeFiles/ch16_addition.dir/build.make
ch16_addition: CMakeFiles/ch16_addition.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ch16_addition"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ch16_addition.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ch16_addition.dir/build: ch16_addition

.PHONY : CMakeFiles/ch16_addition.dir/build

CMakeFiles/ch16_addition.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ch16_addition.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ch16_addition.dir/clean

CMakeFiles/ch16_addition.dir/depend:
	cd "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16" "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16" "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/cmake-build-debug" "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/cmake-build-debug" "/Users/elvir/CLionProjects/The Art of Multiprocessor Programming/ch16/cmake-build-debug/CMakeFiles/ch16_addition.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ch16_addition.dir/depend

