# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/ppetrica/Programs/cmake-3.12.1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/ppetrica/Programs/cmake-3.12.1-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ppetrica/Renderel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ppetrica/Renderel/build

# Include any dependencies generated for this target.
include lib/glew/build/cmake/CMakeFiles/glew_s.dir/depend.make

# Include the progress variables for this target.
include lib/glew/build/cmake/CMakeFiles/glew_s.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glew/build/cmake/CMakeFiles/glew_s.dir/flags.make

lib/glew/build/cmake/CMakeFiles/glew_s.dir/__/__/src/glew.c.o: lib/glew/build/cmake/CMakeFiles/glew_s.dir/flags.make
lib/glew/build/cmake/CMakeFiles/glew_s.dir/__/__/src/glew.c.o: ../lib/glew/src/glew.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ppetrica/Renderel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/glew/build/cmake/CMakeFiles/glew_s.dir/__/__/src/glew.c.o"
	cd /home/ppetrica/Renderel/build/lib/glew/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glew_s.dir/__/__/src/glew.c.o   -c /home/ppetrica/Renderel/lib/glew/src/glew.c

lib/glew/build/cmake/CMakeFiles/glew_s.dir/__/__/src/glew.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glew_s.dir/__/__/src/glew.c.i"
	cd /home/ppetrica/Renderel/build/lib/glew/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ppetrica/Renderel/lib/glew/src/glew.c > CMakeFiles/glew_s.dir/__/__/src/glew.c.i

lib/glew/build/cmake/CMakeFiles/glew_s.dir/__/__/src/glew.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glew_s.dir/__/__/src/glew.c.s"
	cd /home/ppetrica/Renderel/build/lib/glew/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ppetrica/Renderel/lib/glew/src/glew.c -o CMakeFiles/glew_s.dir/__/__/src/glew.c.s

# Object files for target glew_s
glew_s_OBJECTS = \
"CMakeFiles/glew_s.dir/__/__/src/glew.c.o"

# External object files for target glew_s
glew_s_EXTERNAL_OBJECTS =

lib/libGLEWd.a: lib/glew/build/cmake/CMakeFiles/glew_s.dir/__/__/src/glew.c.o
lib/libGLEWd.a: lib/glew/build/cmake/CMakeFiles/glew_s.dir/build.make
lib/libGLEWd.a: lib/glew/build/cmake/CMakeFiles/glew_s.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ppetrica/Renderel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../../../libGLEWd.a"
	cd /home/ppetrica/Renderel/build/lib/glew/build/cmake && $(CMAKE_COMMAND) -P CMakeFiles/glew_s.dir/cmake_clean_target.cmake
	cd /home/ppetrica/Renderel/build/lib/glew/build/cmake && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glew_s.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glew/build/cmake/CMakeFiles/glew_s.dir/build: lib/libGLEWd.a

.PHONY : lib/glew/build/cmake/CMakeFiles/glew_s.dir/build

lib/glew/build/cmake/CMakeFiles/glew_s.dir/clean:
	cd /home/ppetrica/Renderel/build/lib/glew/build/cmake && $(CMAKE_COMMAND) -P CMakeFiles/glew_s.dir/cmake_clean.cmake
.PHONY : lib/glew/build/cmake/CMakeFiles/glew_s.dir/clean

lib/glew/build/cmake/CMakeFiles/glew_s.dir/depend:
	cd /home/ppetrica/Renderel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ppetrica/Renderel /home/ppetrica/Renderel/lib/glew/build/cmake /home/ppetrica/Renderel/build /home/ppetrica/Renderel/build/lib/glew/build/cmake /home/ppetrica/Renderel/build/lib/glew/build/cmake/CMakeFiles/glew_s.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glew/build/cmake/CMakeFiles/glew_s.dir/depend
