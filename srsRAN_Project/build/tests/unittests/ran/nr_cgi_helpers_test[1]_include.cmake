if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/nr_cgi_helpers_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/nr_cgi_helpers_test[1]_tests.cmake")
else()
  add_test(nr_cgi_helpers_test_NOT_BUILT nr_cgi_helpers_test_NOT_BUILT)
endif()
