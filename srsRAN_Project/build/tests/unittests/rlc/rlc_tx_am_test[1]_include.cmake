if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_tx_am_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_tx_am_test[1]_tests.cmake")
else()
  add_test(rlc_tx_am_test_NOT_BUILT rlc_tx_am_test_NOT_BUILT)
endif()