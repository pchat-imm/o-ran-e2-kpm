if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/sdap/sdap_tx_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/sdap/sdap_tx_test[1]_tests.cmake")
else()
  add_test(sdap_tx_test_NOT_BUILT sdap_tx_test_NOT_BUILT)
endif()