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
CMAKE_SOURCE_DIR = /home/oem/o-ran-e2/srsRAN_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oem/o-ran-e2/srsRAN_Project/build

# Include any dependencies generated for this target.
include tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/flags.make

tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o: tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/flags.make
tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o: ../tests/unittests/phy/lower/modulation/ofdm_modulator_unittest.cpp
tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o: tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oem/o-ran-e2/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o"
	cd /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/lower/modulation && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o -MF CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o.d -o CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o -c /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/lower/modulation/ofdm_modulator_unittest.cpp

tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.i"
	cd /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/lower/modulation && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/lower/modulation/ofdm_modulator_unittest.cpp > CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.i

tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.s"
	cd /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/lower/modulation && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/lower/modulation/ofdm_modulator_unittest.cpp -o CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.s

# Object files for target ofdm_modulator_unittest
ofdm_modulator_unittest_OBJECTS = \
"CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o"

# External object files for target ofdm_modulator_unittest
ofdm_modulator_unittest_EXTERNAL_OBJECTS =

tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/ofdm_modulator_unittest.cpp.o
tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/build.make
tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: lib/srslog/libsrslog.a
tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: lib/phy/lower/modulation/libsrsran_lower_phy_modulation.a
tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: lib/srsvec/libsrsvec.a
tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: lib/ran/libsrsran_ran.a
tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: lib/srslog/libsrslog.a
tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: external/fmt/libfmt.a
tests/unittests/phy/lower/modulation/ofdm_modulator_unittest: tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oem/o-ran-e2/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ofdm_modulator_unittest"
	cd /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/lower/modulation && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ofdm_modulator_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/build: tests/unittests/phy/lower/modulation/ofdm_modulator_unittest
.PHONY : tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/build

tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/clean:
	cd /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/lower/modulation && $(CMAKE_COMMAND) -P CMakeFiles/ofdm_modulator_unittest.dir/cmake_clean.cmake
.PHONY : tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/clean

tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/depend:
	cd /home/oem/o-ran-e2/srsRAN_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oem/o-ran-e2/srsRAN_Project /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/lower/modulation /home/oem/o-ran-e2/srsRAN_Project/build /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/lower/modulation /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/unittests/phy/lower/modulation/CMakeFiles/ofdm_modulator_unittest.dir/depend
