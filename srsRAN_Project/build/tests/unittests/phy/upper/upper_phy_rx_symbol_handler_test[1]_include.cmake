if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/phy/upper/upper_phy_rx_symbol_handler_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/phy/upper/upper_phy_rx_symbol_handler_test[1]_tests.cmake")
else()
  add_test(upper_phy_rx_symbol_handler_test_NOT_BUILT upper_phy_rx_symbol_handler_test_NOT_BUILT)
endif()
