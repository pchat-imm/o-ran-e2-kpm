if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/integrationtests/du_high_cu/cu_du_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/integrationtests/du_high_cu/cu_du_test[1]_tests.cmake")
else()
  add_test(cu_du_test_NOT_BUILT cu_du_test_NOT_BUILT)
endif()