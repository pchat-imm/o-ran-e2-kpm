add_test( fapi_to_phy_translator_fixture.downlink_processor_is_not_configured_on_new_slot /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy/fapi_to_phy_translator_test [==[--gtest_filter=fapi_to_phy_translator_fixture.downlink_processor_is_not_configured_on_new_slot]==] --gtest_also_run_disabled_tests)
set_tests_properties( fapi_to_phy_translator_fixture.downlink_processor_is_not_configured_on_new_slot PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( fapi_to_phy_translator_fixture.downlink_processor_is_configured_on_new_dl_tti_request /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy/fapi_to_phy_translator_test [==[--gtest_filter=fapi_to_phy_translator_fixture.downlink_processor_is_configured_on_new_dl_tti_request]==] --gtest_also_run_disabled_tests)
set_tests_properties( fapi_to_phy_translator_fixture.downlink_processor_is_configured_on_new_dl_tti_request PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( fapi_to_phy_translator_fixture.current_grid_is_sent_on_new_slot /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy/fapi_to_phy_translator_test [==[--gtest_filter=fapi_to_phy_translator_fixture.current_grid_is_sent_on_new_slot]==] --gtest_also_run_disabled_tests)
set_tests_properties( fapi_to_phy_translator_fixture.current_grid_is_sent_on_new_slot PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( fapi_to_phy_translator_fixture.dl_ssb_pdu_is_processed /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy/fapi_to_phy_translator_test [==[--gtest_filter=fapi_to_phy_translator_fixture.dl_ssb_pdu_is_processed]==] --gtest_also_run_disabled_tests)
set_tests_properties( fapi_to_phy_translator_fixture.dl_ssb_pdu_is_processed PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( fapi_to_phy_translator_fixture.calling_dl_tti_request_without_handling_slot_does_nothing /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy/fapi_to_phy_translator_test [==[--gtest_filter=fapi_to_phy_translator_fixture.calling_dl_tti_request_without_handling_slot_does_nothing]==] --gtest_also_run_disabled_tests)
set_tests_properties( fapi_to_phy_translator_fixture.calling_dl_tti_request_without_handling_slot_does_nothing PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/fapi_adaptor/phy SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( fapi_to_phy_translator_test_TESTS fapi_to_phy_translator_fixture.downlink_processor_is_not_configured_on_new_slot fapi_to_phy_translator_fixture.downlink_processor_is_configured_on_new_dl_tti_request fapi_to_phy_translator_fixture.current_grid_is_sent_on_new_slot fapi_to_phy_translator_fixture.dl_ssb_pdu_is_processed fapi_to_phy_translator_fixture.calling_dl_tti_request_without_handling_slot_does_nothing)