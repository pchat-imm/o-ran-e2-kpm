add_test( ofh_uplane_prach_data_flow_notifier.empty_context_does_not_notify /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver/ofh_uplane_prach_data_flow_notifier_test [==[--gtest_filter=ofh_uplane_prach_data_flow_notifier.empty_context_does_not_notify]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_prach_data_flow_notifier.empty_context_does_not_notify PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ofh_uplane_prach_data_flow_notifier.unwritten_buffer_does_not_notify /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver/ofh_uplane_prach_data_flow_notifier_test [==[--gtest_filter=ofh_uplane_prach_data_flow_notifier.unwritten_buffer_does_not_notify]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_prach_data_flow_notifier.unwritten_buffer_does_not_notify PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ofh_uplane_prach_data_flow_notifier.completed_long_prach_buffer_triggers_notification /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver/ofh_uplane_prach_data_flow_notifier_test [==[--gtest_filter=ofh_uplane_prach_data_flow_notifier.completed_long_prach_buffer_triggers_notification]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_prach_data_flow_notifier.completed_long_prach_buffer_triggers_notification PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ofh_uplane_prach_data_flow_notifier.completed_short_prach_buffer_triggers_notification /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver/ofh_uplane_prach_data_flow_notifier_test [==[--gtest_filter=ofh_uplane_prach_data_flow_notifier.completed_short_prach_buffer_triggers_notification]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_prach_data_flow_notifier.completed_short_prach_buffer_triggers_notification PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/receiver SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( ofh_uplane_prach_data_flow_notifier_test_TESTS ofh_uplane_prach_data_flow_notifier.empty_context_does_not_notify ofh_uplane_prach_data_flow_notifier.unwritten_buffer_does_not_notify ofh_uplane_prach_data_flow_notifier.completed_long_prach_buffer_triggers_notification ofh_uplane_prach_data_flow_notifier.completed_short_prach_buffer_triggers_notification)