add_test( bounded_integer_test.valid_method /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.valid_method]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.valid_method PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.value_comparison /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.value_comparison]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.value_comparison PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.cast_to_integer /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.cast_to_integer]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.cast_to_integer PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.copy_ctor /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.copy_ctor]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.copy_ctor PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.copy_assignment /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.copy_assignment]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.copy_assignment PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.increment_decrement_operator /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.increment_decrement_operator]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.increment_decrement_operator PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.addition_subtraction_with_raw_integers /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.addition_subtraction_with_raw_integers]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.addition_subtraction_with_raw_integers PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.addition_subtraction_with_other_bounded_integers /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.addition_subtraction_with_other_bounded_integers]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.addition_subtraction_with_other_bounded_integers PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.fmt_format /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.fmt_format]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.fmt_format PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( bounded_integer_test.fmt_format_when_out_of_bounds /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt/bounded_integer_test [==[--gtest_filter=bounded_integer_test.fmt_format_when_out_of_bounds]==] --gtest_also_run_disabled_tests)
set_tests_properties( bounded_integer_test.fmt_format_when_out_of_bounds PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/adt SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( bounded_integer_test_TESTS bounded_integer_test.valid_method bounded_integer_test.value_comparison bounded_integer_test.cast_to_integer bounded_integer_test.copy_ctor bounded_integer_test.copy_assignment bounded_integer_test.increment_decrement_operator bounded_integer_test.addition_subtraction_with_raw_integers bounded_integer_test.addition_subtraction_with_other_bounded_integers bounded_integer_test.fmt_format bounded_integer_test.fmt_format_when_out_of_bounds)