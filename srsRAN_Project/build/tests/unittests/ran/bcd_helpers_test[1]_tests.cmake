add_test( bcd_helpers_test.plmn_string_to_bcd /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/bcd_helpers_test [==[--gtest_filter=bcd_helpers_test.plmn_string_to_bcd]==] --gtest_also_run_disabled_tests)
set_tests_properties( bcd_helpers_test.plmn_string_to_bcd PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bcd_helpers_test.plmn_bcd_to_string /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/bcd_helpers_test [==[--gtest_filter=bcd_helpers_test.plmn_bcd_to_string]==] --gtest_also_run_disabled_tests)
set_tests_properties( bcd_helpers_test.plmn_bcd_to_string PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( bcd_helpers_test_TESTS bcd_helpers_test.plmn_string_to_bcd bcd_helpers_test.plmn_bcd_to_string)
