add_test( UplinkProcessor.calling_process_prach_enqueue_task /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper/uplink_processor_test [==[--gtest_filter=UplinkProcessor.calling_process_prach_enqueue_task]==] --gtest_also_run_disabled_tests)
set_tests_properties( UplinkProcessor.calling_process_prach_enqueue_task PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( UplinkProcessor.after_detect_prach_is_executed_results_notifier_is_called /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper/uplink_processor_test [==[--gtest_filter=UplinkProcessor.after_detect_prach_is_executed_results_notifier_is_called]==] --gtest_also_run_disabled_tests)
set_tests_properties( UplinkProcessor.after_detect_prach_is_executed_results_notifier_is_called PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( uplink_processor_test_TESTS UplinkProcessor.calling_process_prach_enqueue_task UplinkProcessor.after_detect_prach_is_executed_results_notifier_is_called)