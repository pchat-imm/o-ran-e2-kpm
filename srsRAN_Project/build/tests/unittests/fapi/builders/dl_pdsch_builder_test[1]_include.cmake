if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi/builders/dl_pdsch_builder_test[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi/builders/dl_pdsch_builder_test[1]_tests.cmake")
else()
  add_test(dl_pdsch_builder_test_NOT_BUILT dl_pdsch_builder_test_NOT_BUILT)
endif()