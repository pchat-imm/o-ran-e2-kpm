# CMake generated Testfile for 
# Source directory: /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/lower
# Build directory: /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/lower
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(lower_phy_test "lower_phy_test")
set_tests_properties(lower_phy_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/lower/CMakeLists.txt;26;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/lower/CMakeLists.txt;0;")
subdirs("modulation")
subdirs("processors")
