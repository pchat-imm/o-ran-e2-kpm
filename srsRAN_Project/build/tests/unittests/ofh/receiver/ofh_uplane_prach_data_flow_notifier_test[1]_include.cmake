if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver/ofh_uplane_prach_data_flow_notifier_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver/ofh_uplane_prach_data_flow_notifier_test[1]_tests.cmake")
else()
  add_test(ofh_uplane_prach_data_flow_notifier_test_NOT_BUILT ofh_uplane_prach_data_flow_notifier_test_NOT_BUILT)
endif()