if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/support/task_worker_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/support/task_worker_test[1]_tests.cmake")
else()
  add_test(task_worker_test_NOT_BUILT task_worker_test_NOT_BUILT)
endif()
