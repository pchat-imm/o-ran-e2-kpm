if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/fapi/validators/uci_indication_validator_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/fapi/validators/uci_indication_validator_test[1]_tests.cmake")
else()
  add_test(uci_indication_validator_test_NOT_BUILT uci_indication_validator_test_NOT_BUILT)
endif()