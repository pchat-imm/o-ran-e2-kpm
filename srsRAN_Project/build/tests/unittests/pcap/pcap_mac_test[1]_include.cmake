if(EXISTS "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/pcap/pcap_mac_test[1]_tests.cmake")
  include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/pcap/pcap_mac_test[1]_tests.cmake")
else()
  add_test(pcap_mac_test_NOT_BUILT pcap_mac_test_NOT_BUILT)
endif()