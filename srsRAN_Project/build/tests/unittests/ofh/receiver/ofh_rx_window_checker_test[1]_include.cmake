if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/ofh/receiver/ofh_rx_window_checker_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/ofh/receiver/ofh_rx_window_checker_test[1]_tests.cmake")
else()
  add_test(ofh_rx_window_checker_test_NOT_BUILT ofh_rx_window_checker_test_NOT_BUILT)
endif()