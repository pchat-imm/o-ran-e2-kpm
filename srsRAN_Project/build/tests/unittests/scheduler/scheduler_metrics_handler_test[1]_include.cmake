if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/scheduler/scheduler_metrics_handler_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/scheduler/scheduler_metrics_handler_test[1]_tests.cmake")
else()
  add_test(scheduler_metrics_handler_test_NOT_BUILT scheduler_metrics_handler_test_NOT_BUILT)
endif()