if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/support/precoding_configuration_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/support/precoding_configuration_test[1]_tests.cmake")
else()
  add_test(precoding_configuration_test_NOT_BUILT precoding_configuration_test_NOT_BUILT)
endif()