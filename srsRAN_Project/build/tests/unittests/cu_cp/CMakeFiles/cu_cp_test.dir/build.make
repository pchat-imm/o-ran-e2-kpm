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
include tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/flags.make

tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o: tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/flags.make
tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o: ../tests/unittests/cu_cp/cu_cp_test.cpp
tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o: tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o -MF CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o.d -o CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o -c /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/cu_cp/cu_cp_test.cpp

tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.i"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/cu_cp/cu_cp_test.cpp > CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.i

tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.s"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/cu_cp/cu_cp_test.cpp -o CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.s

# Object files for target cu_cp_test
cu_cp_test_OBJECTS = \
"CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o"

# External object files for target cu_cp_test
cu_cp_test_EXTERNAL_OBJECTS =

tests/unittests/cu_cp/cu_cp_test: tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/cu_cp_test.cpp.o
tests/unittests/cu_cp/cu_cp_test: tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/build.make
tests/unittests/cu_cp/cu_cp_test: tests/unittests/cu_cp/libcu_cp_test_helpers.a
tests/unittests/cu_cp/cu_cp_test: tests/unittests/f1ap/cu_cp/libf1ap_cu_test_helpers.a
tests/unittests/cu_cp/cu_cp_test: tests/unittests/ngap/libngap_test_helpers.a
tests/unittests/cu_cp/cu_cp_test: tests/unittests/rrc/librrc_ue_test_helpers.a
tests/unittests/cu_cp/cu_cp_test: lib/cu_cp/libsrsran_cu_cp.a
tests/unittests/cu_cp/cu_cp_test: lib/support/libsrsran_support.a
tests/unittests/cu_cp/cu_cp_test: lib/srslog/libsrslog.a
tests/unittests/cu_cp/cu_cp_test: lib/asn1/libf1ap_asn1.a
tests/unittests/cu_cp/cu_cp_test: lib/asn1/libngap_asn1.a
tests/unittests/cu_cp/cu_cp_test: lib/ngap/libsrsran_ngap.a
tests/unittests/cu_cp/cu_cp_test: lib/cu_cp/libsrsran_cu_cp.a
tests/unittests/cu_cp/cu_cp_test: lib/ngap/libsrsran_ngap.a
tests/unittests/cu_cp/cu_cp_test: lib/cu_cp/cell_meas_manager/libsrsran_cu_cp_cell_meas_manager.a
tests/unittests/cu_cp/cu_cp_test: lib/cu_cp/mobility_manager/libsrsran_cu_cp_mobility_manager.a
tests/unittests/cu_cp/cu_cp_test: lib/ran/libsrsran_ran.a
tests/unittests/cu_cp/cu_cp_test: lib/e1ap/libsrsran_e1ap.a
tests/unittests/cu_cp/cu_cp_test: lib/rrc/libsrsran_rrc.a
tests/unittests/cu_cp/cu_cp_test: lib/cu_cp/up_resource_manager/libsrsran_up_resource_manager.a
tests/unittests/cu_cp/cu_cp_test: lib/pdcp/libsrsran_pdcp.a
tests/unittests/cu_cp/cu_cp_test: lib/asn1/librrc_nr_asn1.a
tests/unittests/cu_cp/cu_cp_test: lib/security/libsrsran_security.a
tests/unittests/cu_cp/cu_cp_test: /usr/lib/x86_64-linux-gnu/libmbedcrypto.so
tests/unittests/cu_cp/cu_cp_test: tests/unittests/e1ap/common/libe1ap_test_helpers.a
tests/unittests/cu_cp/cu_cp_test: lib/asn1/libe1ap_asn1.a
tests/unittests/cu_cp/cu_cp_test: tests/unittests/f1ap/common/libf1ap_test_helpers.a
tests/unittests/cu_cp/cu_cp_test: lib/f1ap/du/libsrsran_f1ap_du.a
tests/unittests/cu_cp/cu_cp_test: lib/f1ap/du/procedures/libsrsran_f1ap_du_procedures.a
tests/unittests/cu_cp/cu_cp_test: lib/f1u/libsrsran_f1u_du.a
tests/unittests/cu_cp/cu_cp_test: lib/f1ap/cu_cp/libsrsran_f1ap_cu.a
tests/unittests/cu_cp/cu_cp_test: lib/f1ap/common/libsrsran_f1ap_common.a
tests/unittests/cu_cp/cu_cp_test: lib/asn1/libf1ap_asn1.a
tests/unittests/cu_cp/cu_cp_test: lib/asn1/libngap_asn1.a
tests/unittests/cu_cp/cu_cp_test: lib/asn1/libasn1_utils.a
tests/unittests/cu_cp/cu_cp_test: lib/support/libsrsran_support.a
tests/unittests/cu_cp/cu_cp_test: lib/support/network/libsrsran_network.a
tests/unittests/cu_cp/cu_cp_test: /usr/lib/x86_64-linux-gnu/libyaml-cpp.so
tests/unittests/cu_cp/cu_cp_test: lib/srslog/libsrslog.a
tests/unittests/cu_cp/cu_cp_test: external/fmt/libfmt.a
tests/unittests/cu_cp/cu_cp_test: tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cu_cp_test"
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cu_cp_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp && /usr/bin/cmake -D TEST_TARGET=cu_cp_test -D TEST_EXECUTABLE=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp/cu_cp_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=cu_cp_test_TESTS -D CTEST_FILE=/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp/cu_cp_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=15 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/build: tests/unittests/cu_cp/cu_cp_test
.PHONY : tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/build

tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/clean:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp && $(CMAKE_COMMAND) -P CMakeFiles/cu_cp_test.dir/cmake_clean.cmake
.PHONY : tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/clean

tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/depend:
	cd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chatchamon/o-ran-e2-kpm/srsRAN_Project /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/cu_cp /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/unittests/cu_cp/CMakeFiles/cu_cp_test.dir/depend
