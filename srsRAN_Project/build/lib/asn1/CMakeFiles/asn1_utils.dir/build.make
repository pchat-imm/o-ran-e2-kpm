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
CMAKE_SOURCE_DIR = /home/chatchamon/o-ran-e2-kpm/srsRAN_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build

# Include any dependencies generated for this target.
include lib/asn1/CMakeFiles/asn1_utils.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/asn1/CMakeFiles/asn1_utils.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/asn1/CMakeFiles/asn1_utils.dir/progress.make

# Include the compile flags for this target's objects.
include lib/asn1/CMakeFiles/asn1_utils.dir/flags.make

lib/asn1/CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o: lib/asn1/CMakeFiles/asn1_utils.dir/flags.make
lib/asn1/CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o: ../lib/asn1/asn1_utils.cpp
lib/asn1/CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o: lib/asn1/CMakeFiles/asn1_utils.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/asn1/CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/asn1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/asn1/CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o -MF CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o.d -o CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o -c /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/asn1/asn1_utils.cpp

lib/asn1/CMakeFiles/asn1_utils.dir/asn1_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/asn1_utils.dir/asn1_utils.cpp.i"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/asn1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/asn1/asn1_utils.cpp > CMakeFiles/asn1_utils.dir/asn1_utils.cpp.i

lib/asn1/CMakeFiles/asn1_utils.dir/asn1_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/asn1_utils.dir/asn1_utils.cpp.s"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/asn1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/asn1/asn1_utils.cpp -o CMakeFiles/asn1_utils.dir/asn1_utils.cpp.s

# Object files for target asn1_utils
asn1_utils_OBJECTS = \
"CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o"

# External object files for target asn1_utils
asn1_utils_EXTERNAL_OBJECTS =

lib/asn1/libasn1_utils.a: lib/asn1/CMakeFiles/asn1_utils.dir/asn1_utils.cpp.o
lib/asn1/libasn1_utils.a: lib/asn1/CMakeFiles/asn1_utils.dir/build.make
lib/asn1/libasn1_utils.a: lib/asn1/CMakeFiles/asn1_utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libasn1_utils.a"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/asn1 && $(CMAKE_COMMAND) -P CMakeFiles/asn1_utils.dir/cmake_clean_target.cmake
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/asn1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/asn1_utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/asn1/CMakeFiles/asn1_utils.dir/build: lib/asn1/libasn1_utils.a
.PHONY : lib/asn1/CMakeFiles/asn1_utils.dir/build

lib/asn1/CMakeFiles/asn1_utils.dir/clean:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/asn1 && $(CMAKE_COMMAND) -P CMakeFiles/asn1_utils.dir/cmake_clean.cmake
.PHONY : lib/asn1/CMakeFiles/asn1_utils.dir/clean

lib/asn1/CMakeFiles/asn1_utils.dir/depend:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chatchamon/o-ran-e2-kpm/srsRAN_Project /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/asn1 /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/asn1 /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/asn1/CMakeFiles/asn1_utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/asn1/CMakeFiles/asn1_utils.dir/depend
