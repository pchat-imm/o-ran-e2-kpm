if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi/validators/dl_tti_request_validator_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi/validators/dl_tti_request_validator_test[1]_tests.cmake")
else()
  add_test(dl_tti_request_validator_test_NOT_BUILT dl_tti_request_validator_test_NOT_BUILT)
endif()