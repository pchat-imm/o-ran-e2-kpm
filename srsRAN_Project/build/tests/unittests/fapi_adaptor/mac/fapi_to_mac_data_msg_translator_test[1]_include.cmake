if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/mac/fapi_to_mac_data_msg_translator_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/mac/fapi_to_mac_data_msg_translator_test[1]_tests.cmake")
else()
  add_test(fapi_to_mac_data_msg_translator_test_NOT_BUILT fapi_to_mac_data_msg_translator_test_NOT_BUILT)
endif()