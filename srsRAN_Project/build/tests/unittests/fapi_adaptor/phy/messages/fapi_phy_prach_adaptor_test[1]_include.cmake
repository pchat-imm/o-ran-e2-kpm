if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy/messages/fapi_phy_prach_adaptor_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy/messages/fapi_phy_prach_adaptor_test[1]_tests.cmake")
else()
  add_test(fapi_phy_prach_adaptor_test_NOT_BUILT fapi_phy_prach_adaptor_test_NOT_BUILT)
endif()