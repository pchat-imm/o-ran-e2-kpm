if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/csi_report_on_pusch_helpers_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/csi_report_on_pusch_helpers_test[1]_tests.cmake")
else()
  add_test(csi_report_on_pusch_helpers_test_NOT_BUILT csi_report_on_pusch_helpers_test_NOT_BUILT)
endif()