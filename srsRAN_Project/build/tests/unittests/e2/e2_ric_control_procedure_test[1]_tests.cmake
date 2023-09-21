add_test( e2_test_setup.ric_control_procedure_setup /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/e2/e2_ric_control_procedure_test [==[--gtest_filter=e2_test_setup.ric_control_procedure_setup]==] --gtest_also_run_disabled_tests)
set_tests_properties( e2_test_setup.ric_control_procedure_setup PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/e2 SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( e2_ric_control_procedure_test_TESTS e2_test_setup.ric_control_procedure_setup)
