if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi/builders/crc_indication_builder_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi/builders/crc_indication_builder_test[1]_tests.cmake")
else()
  add_test(crc_indication_builder_test_NOT_BUILT crc_indication_builder_test_NOT_BUILT)
endif()