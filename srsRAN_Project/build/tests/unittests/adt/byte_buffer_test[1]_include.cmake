if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/byte_buffer_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/byte_buffer_test[1]_tests.cmake")
else()
  add_test(byte_buffer_test_NOT_BUILT byte_buffer_test_NOT_BUILT)
endif()