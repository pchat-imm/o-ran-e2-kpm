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
include lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/progress.make

# Include the compile flags for this target's objects.
include lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/flags.make

lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o: lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/flags.make
lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o: ../lib/f1u/local_connector/f1u_local_connector.cpp
lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o: lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/f1u && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o -MF CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o.d -o CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o -c /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/f1u/local_connector/f1u_local_connector.cpp

lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.i"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/f1u && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/f1u/local_connector/f1u_local_connector.cpp > CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.i

lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.s"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/f1u && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/f1u/local_connector/f1u_local_connector.cpp -o CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.s

# Object files for target srsgnb_app_f1u_connector
srsgnb_app_f1u_connector_OBJECTS = \
"CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o"

# External object files for target srsgnb_app_f1u_connector
srsgnb_app_f1u_connector_EXTERNAL_OBJECTS =

lib/f1u/libsrsgnb_app_f1u_connector.a: lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/local_connector/f1u_local_connector.cpp.o
lib/f1u/libsrsgnb_app_f1u_connector.a: lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/build.make
lib/f1u/libsrsgnb_app_f1u_connector.a: lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsrsgnb_app_f1u_connector.a"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/f1u && $(CMAKE_COMMAND) -P CMakeFiles/srsgnb_app_f1u_connector.dir/cmake_clean_target.cmake
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/f1u && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/srsgnb_app_f1u_connector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/build: lib/f1u/libsrsgnb_app_f1u_connector.a
.PHONY : lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/build

lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/clean:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/f1u && $(CMAKE_COMMAND) -P CMakeFiles/srsgnb_app_f1u_connector.dir/cmake_clean.cmake
.PHONY : lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/clean

lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/depend:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chatchamon/o-ran-e2-kpm/srsRAN_Project /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/f1u /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/f1u /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/f1u/CMakeFiles/srsgnb_app_f1u_connector.dir/depend
