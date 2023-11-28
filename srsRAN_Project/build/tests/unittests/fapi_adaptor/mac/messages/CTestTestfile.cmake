# CMake generated Testfile for 
# Source directory: /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/fapi_adaptor/mac/messages
# Build directory: /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/fapi_adaptor/mac/messages
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/fapi_adaptor/mac/messages/mac_fapi_prach_adaptor_test[1]_include.cmake")
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/fapi_adaptor/mac/messages/mac_fapi_pucch_adaptor_test[1]_include.cmake")
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/fapi_adaptor/mac/messages/mac_fapi_pusch_adaptor_test[1]_include.cmake")
add_test(mac_fapi_pdcch_adaptor_test "mac_fapi_pdcch_adaptor_test")
set_tests_properties(mac_fapi_pdcch_adaptor_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/fapi_adaptor/mac/messages/CMakeLists.txt;25;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/fapi_adaptor/mac/messages/CMakeLists.txt;0;")
add_test(mac_fapi_pdsch_adaptor_test "mac_fapi_pdsch_adaptor_test")
set_tests_properties(mac_fapi_pdsch_adaptor_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/fapi_adaptor/mac/messages/CMakeLists.txt;29;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/fapi_adaptor/mac/messages/CMakeLists.txt;0;")
add_test(mac_fapi_ssb_adaptor_test "mac_fapi_ssb_adaptor_test")
set_tests_properties(mac_fapi_ssb_adaptor_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/fapi_adaptor/mac/messages/CMakeLists.txt;33;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/fapi_adaptor/mac/messages/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "fapi_adaptor")
