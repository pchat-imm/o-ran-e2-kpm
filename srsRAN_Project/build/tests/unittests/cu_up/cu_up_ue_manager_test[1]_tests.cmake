add_test( ue_manager_test.when_ue_db_not_full_new_ue_can_be_added /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/cu_up/cu_up_ue_manager_test [==[--gtest_filter=ue_manager_test.when_ue_db_not_full_new_ue_can_be_added]==] --gtest_also_run_disabled_tests)
set_tests_properties( ue_manager_test.when_ue_db_not_full_new_ue_can_be_added PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/cu_up SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ue_manager_test.when_ue_db_is_full_new_ue_cannot_be_added /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/cu_up/cu_up_ue_manager_test [==[--gtest_filter=ue_manager_test.when_ue_db_is_full_new_ue_cannot_be_added]==] --gtest_also_run_disabled_tests)
set_tests_properties( ue_manager_test.when_ue_db_is_full_new_ue_cannot_be_added PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/cu_up SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ue_manager_test.when_ue_are_deleted_ue_db_is_empty /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/cu_up/cu_up_ue_manager_test [==[--gtest_filter=ue_manager_test.when_ue_are_deleted_ue_db_is_empty]==] --gtest_also_run_disabled_tests)
set_tests_properties( ue_manager_test.when_ue_are_deleted_ue_db_is_empty PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/cu_up SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( cu_up_ue_manager_test_TESTS ue_manager_test.when_ue_db_not_full_new_ue_can_be_added ue_manager_test.when_ue_db_is_full_new_ue_cannot_be_added ue_manager_test.when_ue_are_deleted_ue_db_is_empty)