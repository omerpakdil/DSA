# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/build

# Include any dependencies generated for this target.
include CMakeFiles/recursion_examples.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/recursion_examples.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/recursion_examples.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/recursion_examples.dir/flags.make

CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o: CMakeFiles/recursion_examples.dir/flags.make
CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o: ../recursion_examples.cpp
CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o: CMakeFiles/recursion_examples.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o -MF CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o.d -o CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o -c /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/recursion_examples.cpp

CMakeFiles/recursion_examples.dir/recursion_examples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/recursion_examples.dir/recursion_examples.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/recursion_examples.cpp > CMakeFiles/recursion_examples.dir/recursion_examples.cpp.i

CMakeFiles/recursion_examples.dir/recursion_examples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/recursion_examples.dir/recursion_examples.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/recursion_examples.cpp -o CMakeFiles/recursion_examples.dir/recursion_examples.cpp.s

# Object files for target recursion_examples
recursion_examples_OBJECTS = \
"CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o"

# External object files for target recursion_examples
recursion_examples_EXTERNAL_OBJECTS =

recursion_examples: CMakeFiles/recursion_examples.dir/recursion_examples.cpp.o
recursion_examples: CMakeFiles/recursion_examples.dir/build.make
recursion_examples: CMakeFiles/recursion_examples.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable recursion_examples"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/recursion_examples.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/recursion_examples.dir/build: recursion_examples
.PHONY : CMakeFiles/recursion_examples.dir/build

CMakeFiles/recursion_examples.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/recursion_examples.dir/cmake_clean.cmake
.PHONY : CMakeFiles/recursion_examples.dir/clean

CMakeFiles/recursion_examples.dir/depend:
	cd /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/build /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/build /home/omer/Personal/InterviewPrep/DSA/Week4_Recursion/build/CMakeFiles/recursion_examples.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/recursion_examples.dir/depend

