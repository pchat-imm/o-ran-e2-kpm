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
include tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/flags.make

tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o: tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/flags.make
tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o: ../tests/unittests/cu_up/pdu_session_manager_test.cpp
tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o: tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o -MF CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o.d -o CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o -c /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/cu_up/pdu_session_manager_test.cpp

tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.i"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/cu_up/pdu_session_manager_test.cpp > CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.i

tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.s"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/cu_up/pdu_session_manager_test.cpp -o CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.s

# Object files for target pdu_session_manager_test
pdu_session_manager_test_OBJECTS = \
"CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o"

# External object files for target pdu_session_manager_test
pdu_session_manager_test_EXTERNAL_OBJECTS =

tests/unittests/cu_up/pdu_session_manager_test: tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/pdu_session_manager_test.cpp.o
tests/unittests/cu_up/pdu_session_manager_test: tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/build.make
tests/unittests/cu_up/pdu_session_manager_test: lib/cu_up/libsrsran_cu_up.a
tests/unittests/cu_up/pdu_session_manager_test: lib/support/libsrsran_support.a
tests/unittests/cu_up/pdu_session_manager_test: lib/asn1/libe1ap_asn1.a
tests/unittests/cu_up/pdu_session_manager_test: lib/srslog/libsrslog.a
tests/unittests/cu_up/pdu_session_manager_test: lib/e1ap/libsrsran_e1ap.a
tests/unittests/cu_up/pdu_session_manager_test: lib/asn1/libe1ap_asn1.a
tests/unittests/cu_up/pdu_session_manager_test: lib/asn1/libasn1_utils.a
tests/unittests/cu_up/pdu_session_manager_test: lib/gtpu/libsrsran_gtpu.a
tests/unittests/cu_up/pdu_session_manager_test: lib/psup/libsrsran_psup.a
tests/unittests/cu_up/pdu_session_manager_test: lib/pdcp/libsrsran_pdcp.a
tests/unittests/cu_up/pdu_session_manager_test: lib/support/libsrsran_support.a
tests/unittests/cu_up/pdu_session_manager_test: lib/support/network/libsrsran_network.a
tests/unittests/cu_up/pdu_session_manager_test: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so
tests/unittests/cu_up/pdu_session_manager_test: lib/gateways/libsrsran_gateway.a
tests/unittests/cu_up/pdu_session_manager_test: lib/srslog/libsrslog.a
tests/unittests/cu_up/pdu_session_manager_test: external/fmt/libfmt.a
tests/unittests/cu_up/pdu_session_manager_test: /usr/lib/x86_64-linux-gnu/libsctp.so
tests/unittests/cu_up/pdu_session_manager_test: lib/sdap/libsrsran_sdap.a
tests/unittests/cu_up/pdu_session_manager_test: lib/security/libsrsran_security.a
tests/unittests/cu_up/pdu_session_manager_test: /usr/lib/x86_64-linux-gnu/libmbedcrypto.so
tests/unittests/cu_up/pdu_session_manager_test: tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pdu_session_manager_test"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pdu_session_manager_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up && /usr/bin/cmake -D TEST_TARGET=pdu_session_manager_test -D TEST_EXECUTABLE=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up/pdu_session_manager_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=pdu_session_manager_test_TESTS -D CTEST_FILE=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up/pdu_session_manager_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=15 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/build: tests/unittests/cu_up/pdu_session_manager_test
.PHONY : tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/build

tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/clean:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up && $(CMAKE_COMMAND) -P CMakeFiles/pdu_session_manager_test.dir/cmake_clean.cmake
.PHONY : tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/clean

tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/depend:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chatchamon/o-ran-e2-kpm/srsRAN_Project /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/cu_up /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/unittests/cu_up/CMakeFiles/pdu_session_manager_test.dir/depend
