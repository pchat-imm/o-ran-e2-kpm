if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/common_scheduling/common_scheduler_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/common_scheduling/common_scheduler_test[1]_tests.cmake")
else()
  add_test(common_scheduler_test_NOT_BUILT common_scheduler_test_NOT_BUILT)
endif()
