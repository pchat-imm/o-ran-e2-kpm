if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/phy/upper/hard_decision_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/phy/upper/hard_decision_test[1]_tests.cmake")
else()
  add_test(hard_decision_test_NOT_BUILT hard_decision_test_NOT_BUILT)
endif()