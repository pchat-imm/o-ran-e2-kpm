# CMake generated Testfile for 
# Source directory: /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/integrationtests/du_high
# Build directory: /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/integrationtests/du_high
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(du_high_test "du_high_test")
set_tests_properties(du_high_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/integrationtests/du_high/CMakeLists.txt;35;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/integrationtests/du_high/CMakeLists.txt;0;")
add_test(paging_du_high_test "paging_du_high_test")
set_tests_properties(paging_du_high_test PROPERTIES  LABELS "tsan" _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/integrationtests/du_high/CMakeLists.txt;41;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/integrationtests/du_high/CMakeLists.txt;0;")
add_test(mac_test_mode_adapter_test "mac_test_mode_adapter_test")
set_tests_properties(mac_test_mode_adapter_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/integrationtests/du_high/CMakeLists.txt;47;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/integrationtests/du_high/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "du_high;integrationtest")
