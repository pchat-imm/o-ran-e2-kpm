add_test( pcap_mac_test.write_pdu /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/pcap/pcap_mac_test [==[--gtest_filter=pcap_mac_test.write_pdu]==] --gtest_also_run_disabled_tests)
set_tests_properties( pcap_mac_test.write_pdu PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/pcap SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( pcap_mac_test.write_many_spans /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/pcap/pcap_mac_test [==[--gtest_filter=pcap_mac_test.write_many_spans]==] --gtest_also_run_disabled_tests)
set_tests_properties( pcap_mac_test.write_many_spans PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/pcap SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( pcap_mac_test.write_many_byte_buffers /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/pcap/pcap_mac_test [==[--gtest_filter=pcap_mac_test.write_many_byte_buffers]==] --gtest_also_run_disabled_tests)
set_tests_properties( pcap_mac_test.write_many_byte_buffers PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/pcap SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( pcap_mac_test_TESTS pcap_mac_test.write_pdu pcap_mac_test.write_many_spans pcap_mac_test.write_many_byte_buffers)