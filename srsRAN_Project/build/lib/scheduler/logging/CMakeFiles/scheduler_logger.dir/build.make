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
include lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/progress.make

# Include the compile flags for this target's objects.
include lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/flags.make

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/flags.make
lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o: ../lib/scheduler/logging/scheduler_result_logger.cpp
lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o -MF CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o.d -o CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o -c /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_result_logger.cpp

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.i"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_result_logger.cpp > CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.i

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.s"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_result_logger.cpp -o CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.s

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/flags.make
lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o: ../lib/scheduler/logging/scheduler_metric_handler.cpp
lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o -MF CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o.d -o CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o -c /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_metric_handler.cpp

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.i"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_metric_handler.cpp > CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.i

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.s"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_metric_handler.cpp -o CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.s

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/flags.make
lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o: ../lib/scheduler/logging/scheduler_event_logger.cpp
lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o -MF CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o.d -o CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o -c /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_event_logger.cpp

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.i"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_event_logger.cpp > CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.i

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.s"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging/scheduler_event_logger.cpp -o CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.s

# Object files for target scheduler_logger
scheduler_logger_OBJECTS = \
"CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o" \
"CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o" \
"CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o"

# External object files for target scheduler_logger
scheduler_logger_EXTERNAL_OBJECTS =

lib/scheduler/logging/libscheduler_logger.a: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_result_logger.cpp.o
lib/scheduler/logging/libscheduler_logger.a: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_metric_handler.cpp.o
lib/scheduler/logging/libscheduler_logger.a: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/scheduler_event_logger.cpp.o
lib/scheduler/logging/libscheduler_logger.a: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/build.make
lib/scheduler/logging/libscheduler_logger.a: lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libscheduler_logger.a"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && $(CMAKE_COMMAND) -P CMakeFiles/scheduler_logger.dir/cmake_clean_target.cmake
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scheduler_logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/build: lib/scheduler/logging/libscheduler_logger.a
.PHONY : lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/build

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/clean:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging && $(CMAKE_COMMAND) -P CMakeFiles/scheduler_logger.dir/cmake_clean.cmake
.PHONY : lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/clean

lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/depend:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chatchamon/o-ran-e2-kpm/srsRAN_Project /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/lib/scheduler/logging /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/scheduler/logging/CMakeFiles/scheduler_logger.dir/depend
