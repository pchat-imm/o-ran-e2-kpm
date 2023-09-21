# CMake generated Testfile for 
# Source directory: /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/generic_functions
# Build directory: /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/generic_functions
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(dft_processor_generic_test "dft_processor_test" "-F" "generic" "-R" "10")
set_tests_properties(dft_processor_generic_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/generic_functions/CMakeLists.txt;31;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/generic_functions/CMakeLists.txt;0;")
add_test(dft_processor_fftw_test "dft_processor_test" "-F" "fftw" "-R" "10")
set_tests_properties(dft_processor_fftw_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/generic_functions/CMakeLists.txt;33;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/generic_functions/CMakeLists.txt;0;")
subdirs("precoding")
set_directory_properties(PROPERTIES LABELS "phy")
