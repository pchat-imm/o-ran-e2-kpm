if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/e1ap/common/e1ap_asn1_packer_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/e1ap/common/e1ap_asn1_packer_test[1]_tests.cmake")
else()
  add_test(e1ap_asn1_packer_test_NOT_BUILT e1ap_asn1_packer_test_NOT_BUILT)
endif()
