# CMake generated Testfile for 
# Source directory: /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/fapi_adaptor/mac
# Build directory: /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/mac
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/mac/fapi_to_mac_data_msg_translator_test[1]_include.cmake")
add_test(mac_to_fapi_translator_test "mac_to_fapi_translator_test")
set_tests_properties(mac_to_fapi_translator_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/fapi_adaptor/mac/CMakeLists.txt;27;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/fapi_adaptor/mac/CMakeLists.txt;0;")
subdirs("messages")
set_directory_properties(PROPERTIES LABELS "fapi_adaptor")
