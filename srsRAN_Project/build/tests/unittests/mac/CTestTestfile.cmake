# CMake generated Testfile for 
# Source directory: /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac
# Build directory: /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/mac
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/mac/mac_ue_create_test[1]_include.cmake")
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/mac/mac_dl_test[1]_include.cmake")
add_test(mac_ctrl_test "mac_ctrl_test")
set_tests_properties(mac_ctrl_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac/CMakeLists.txt;34;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac/CMakeLists.txt;0;")
add_test(mac_ul_pdu_test "mac_ul_pdu_test")
set_tests_properties(mac_ul_pdu_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac/CMakeLists.txt;38;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac/CMakeLists.txt;0;")
add_test(mac_ul_processor_test "mac_ul_processor_test")
set_tests_properties(mac_ul_processor_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac/CMakeLists.txt;42;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac/CMakeLists.txt;0;")
add_test(mac_dl_test "mac_dl_test")
set_tests_properties(mac_dl_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac/CMakeLists.txt;52;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/mac/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "mac")
