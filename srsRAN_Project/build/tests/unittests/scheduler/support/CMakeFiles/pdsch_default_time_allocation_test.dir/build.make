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
include tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/flags.make

tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o: tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/flags.make
tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o: ../tests/unittests/scheduler/support/pdsch/pdsch_default_time_allocation_test.cpp
tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o: tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/support && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o -MF CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o.d -o CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o -c /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/scheduler/support/pdsch/pdsch_default_time_allocation_test.cpp

tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.i"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/support && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/scheduler/support/pdsch/pdsch_default_time_allocation_test.cpp > CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.i

tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.s"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/support && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/scheduler/support/pdsch/pdsch_default_time_allocation_test.cpp -o CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.s

# Object files for target pdsch_default_time_allocation_test
pdsch_default_time_allocation_test_OBJECTS = \
"CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o"

# External object files for target pdsch_default_time_allocation_test
pdsch_default_time_allocation_test_EXTERNAL_OBJECTS =

tests/unittests/scheduler/support/pdsch_default_time_allocation_test: tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/pdsch/pdsch_default_time_allocation_test.cpp.o
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/build.make
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/scheduler/libsrsran_sched.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/srslog/libsrslog.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/scheduler/config/libsched_config.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/du_manager/ran_resource_management/libdu_resource_manager.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/du_manager/converters/libdu_manager_converters.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/scheduler/libsrsran_sched.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/scheduler/config/libsched_config.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/du_manager/ran_resource_management/libdu_resource_manager.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/du_manager/converters/libdu_manager_converters.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/scheduler/logging/libscheduler_logger.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/du/libsrsran_du_config_validators.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/mac/libmac_configuration_helpers.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/ran/libsrsran_ran.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/asn1/librrc_nr_asn1.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/asn1/libasn1_utils.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/support/libsrsran_support.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/support/network/libsrsran_network.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: lib/srslog/libsrslog.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: external/fmt/libfmt.a
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so
tests/unittests/scheduler/support/pdsch_default_time_allocation_test: tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pdsch_default_time_allocation_test"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/support && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pdsch_default_time_allocation_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/build: tests/unittests/scheduler/support/pdsch_default_time_allocation_test
.PHONY : tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/build

tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/clean:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/support && $(CMAKE_COMMAND) -P CMakeFiles/pdsch_default_time_allocation_test.dir/cmake_clean.cmake
.PHONY : tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/clean

tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/depend:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chatchamon/o-ran-e2-kpm/srsRAN_Project /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/scheduler/support /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/support /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/unittests/scheduler/support/CMakeFiles/pdsch_default_time_allocation_test.dir/depend
