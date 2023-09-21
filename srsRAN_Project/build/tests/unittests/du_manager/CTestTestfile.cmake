# CMake generated Testfile for 
# Source directory: /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/du_manager
# Build directory: /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/du_bearer_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/ue_manager_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/sib_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/serving_cell_config_converter_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/mac_cell_group_config_converter_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/du_manager_ue_creation_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/du_ue_config_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/du_ran_resource_manager_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/du_manager/pucch_resource_generator_test[1]_include.cmake")
add_test(serving_cell_config_converter_test "serving_cell_config_converter_test")
set_tests_properties(serving_cell_config_converter_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/du_manager/CMakeLists.txt;58;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/du_manager/CMakeLists.txt;0;")
add_test(mac_cell_group_config_converter_test "mac_cell_group_config_converter_test")
set_tests_properties(mac_cell_group_config_converter_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/du_manager/CMakeLists.txt;63;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/du_manager/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "du_manager")
