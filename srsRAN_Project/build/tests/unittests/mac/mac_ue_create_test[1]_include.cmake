if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/mac/mac_ue_create_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/mac/mac_ue_create_test[1]_tests.cmake")
else()
  add_test(mac_ue_create_test_NOT_BUILT mac_ue_create_test_NOT_BUILT)
endif()