if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up/cu_up_ue_manager_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/cu_up/cu_up_ue_manager_test[1]_tests.cmake")
else()
  add_test(cu_up_ue_manager_test_NOT_BUILT cu_up_ue_manager_test_NOT_BUILT)
endif()