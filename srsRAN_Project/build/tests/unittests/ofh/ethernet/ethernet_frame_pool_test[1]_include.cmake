if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/ofh/ethernet/ethernet_frame_pool_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/ofh/ethernet/ethernet_frame_pool_test[1]_tests.cmake")
else()
  add_test(ethernet_frame_pool_test_NOT_BUILT ethernet_frame_pool_test_NOT_BUILT)
endif()