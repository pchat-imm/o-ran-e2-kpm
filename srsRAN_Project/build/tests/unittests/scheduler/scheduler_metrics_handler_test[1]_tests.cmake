add_test( scheduler_metrics_handler_tester.metrics_sent_with_defined_periodicity /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/scheduler_metrics_handler_test [==[--gtest_filter=scheduler_metrics_handler_tester.metrics_sent_with_defined_periodicity]==] --gtest_also_run_disabled_tests)
set_tests_properties( scheduler_metrics_handler_tester.metrics_sent_with_defined_periodicity PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( scheduler_metrics_handler_tester.when_no_events_took_place_then_metrics_are_zero /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/scheduler_metrics_handler_test [==[--gtest_filter=scheduler_metrics_handler_tester.when_no_events_took_place_then_metrics_are_zero]==] --gtest_also_run_disabled_tests)
set_tests_properties( scheduler_metrics_handler_tester.when_no_events_took_place_then_metrics_are_zero PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( scheduler_metrics_handler_tester.compute_nof_dl_oks_and_noks /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/scheduler_metrics_handler_test [==[--gtest_filter=scheduler_metrics_handler_tester.compute_nof_dl_oks_and_noks]==] --gtest_also_run_disabled_tests)
set_tests_properties( scheduler_metrics_handler_tester.compute_nof_dl_oks_and_noks PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( scheduler_metrics_handler_tester.compute_nof_ul_oks_and_noks /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/scheduler_metrics_handler_test [==[--gtest_filter=scheduler_metrics_handler_tester.compute_nof_ul_oks_and_noks]==] --gtest_also_run_disabled_tests)
set_tests_properties( scheduler_metrics_handler_tester.compute_nof_ul_oks_and_noks PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( scheduler_metrics_handler_tester.compute_mcs /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/scheduler_metrics_handler_test [==[--gtest_filter=scheduler_metrics_handler_tester.compute_mcs]==] --gtest_also_run_disabled_tests)
set_tests_properties( scheduler_metrics_handler_tester.compute_mcs PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( scheduler_metrics_handler_tester.compute_bitrate /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler/scheduler_metrics_handler_test [==[--gtest_filter=scheduler_metrics_handler_tester.compute_bitrate]==] --gtest_also_run_disabled_tests)
set_tests_properties( scheduler_metrics_handler_tester.compute_bitrate PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/scheduler SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( scheduler_metrics_handler_test_TESTS scheduler_metrics_handler_tester.metrics_sent_with_defined_periodicity scheduler_metrics_handler_tester.when_no_events_took_place_then_metrics_are_zero scheduler_metrics_handler_tester.compute_nof_dl_oks_and_noks scheduler_metrics_handler_tester.compute_nof_ul_oks_and_noks scheduler_metrics_handler_tester.compute_mcs scheduler_metrics_handler_tester.compute_bitrate)