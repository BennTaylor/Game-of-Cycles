# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/build

# Include any dependencies generated for this target.
include CMakeFiles/module_ex.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/module_ex.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/module_ex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/module_ex.dir/flags.make

CMakeFiles/module_ex.dir/binding_test.cpp.o: CMakeFiles/module_ex.dir/flags.make
CMakeFiles/module_ex.dir/binding_test.cpp.o: /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/binding_test.cpp
CMakeFiles/module_ex.dir/binding_test.cpp.o: CMakeFiles/module_ex.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/module_ex.dir/binding_test.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/module_ex.dir/binding_test.cpp.o -MF CMakeFiles/module_ex.dir/binding_test.cpp.o.d -o CMakeFiles/module_ex.dir/binding_test.cpp.o -c /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/binding_test.cpp

CMakeFiles/module_ex.dir/binding_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/module_ex.dir/binding_test.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/binding_test.cpp > CMakeFiles/module_ex.dir/binding_test.cpp.i

CMakeFiles/module_ex.dir/binding_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/module_ex.dir/binding_test.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/binding_test.cpp -o CMakeFiles/module_ex.dir/binding_test.cpp.s

# Object files for target module_ex
module_ex_OBJECTS = \
"CMakeFiles/module_ex.dir/binding_test.cpp.o"

# External object files for target module_ex
module_ex_EXTERNAL_OBJECTS =

module_ex.cpython-39-darwin.so: CMakeFiles/module_ex.dir/binding_test.cpp.o
module_ex.cpython-39-darwin.so: CMakeFiles/module_ex.dir/build.make
module_ex.cpython-39-darwin.so: CMakeFiles/module_ex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module module_ex.cpython-39-darwin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/module_ex.dir/link.txt --verbose=$(VERBOSE)
	/Library/Developer/CommandLineTools/usr/bin/strip -x /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/build/module_ex.cpython-39-darwin.so

# Rule to build all files generated by this target.
CMakeFiles/module_ex.dir/build: module_ex.cpython-39-darwin.so
.PHONY : CMakeFiles/module_ex.dir/build

CMakeFiles/module_ex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/module_ex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/module_ex.dir/clean

CMakeFiles/module_ex.dir/depend:
	cd /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/build /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/build /Users/bentaylor/Desktop/Game_of_Cycles/GOC_visualizer/build/CMakeFiles/module_ex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/module_ex.dir/depend

