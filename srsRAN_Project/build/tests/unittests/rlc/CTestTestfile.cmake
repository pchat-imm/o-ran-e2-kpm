# CMake generated Testfile for 
# Source directory: /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc
# Build directory: /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_rx_am_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_tx_am_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_rx_tm_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_tx_tm_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_um_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_pdu_recycler_test[1]_include.cmake")
add_test(rlc_um_pdu_test "rlc_um_pdu_test")
set_tests_properties(rlc_um_pdu_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc/CMakeLists.txt;51;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc/CMakeLists.txt;0;")
add_test(rlc_am_pdu_test "rlc_am_pdu_test")
set_tests_properties(rlc_am_pdu_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc/CMakeLists.txt;56;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc/CMakeLists.txt;0;")
add_test(rlc_sdu_queue_test "rlc_sdu_queue_test")
set_tests_properties(rlc_sdu_queue_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc/CMakeLists.txt;66;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc/CMakeLists.txt;0;")
add_test(rlc_retx_queue_test "rlc_retx_queue_test")
set_tests_properties(rlc_retx_queue_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc/CMakeLists.txt;71;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/rlc/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "rlc")
