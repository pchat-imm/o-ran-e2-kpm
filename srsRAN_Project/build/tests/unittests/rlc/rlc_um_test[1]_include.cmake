if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_um_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/rlc/rlc_um_test[1]_tests.cmake")
else()
  add_test(rlc_um_test_NOT_BUILT rlc_um_test_NOT_BUILT)
endif()