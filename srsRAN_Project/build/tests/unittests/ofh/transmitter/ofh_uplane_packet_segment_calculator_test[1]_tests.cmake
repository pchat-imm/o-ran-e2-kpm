add_test( ofh_uplane_packet_fragment_calculator.prbs_fit_in_one_segment_passes /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter/ofh_uplane_packet_segment_calculator_test [==[--gtest_filter=ofh_uplane_packet_fragment_calculator.prbs_fit_in_one_segment_passes]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_packet_fragment_calculator.prbs_fit_in_one_segment_passes PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ofh_uplane_packet_fragment_calculator.whole_prb_range_compressed_passes /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter/ofh_uplane_packet_segment_calculator_test [==[--gtest_filter=ofh_uplane_packet_fragment_calculator.whole_prb_range_compressed_passes]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_packet_fragment_calculator.whole_prb_range_compressed_passes PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ofh_uplane_packet_fragment_calculator.whole_prb_range_uncompressed_generates_two_segments /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter/ofh_uplane_packet_segment_calculator_test [==[--gtest_filter=ofh_uplane_packet_fragment_calculator.whole_prb_range_uncompressed_generates_two_segments]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_packet_fragment_calculator.whole_prb_range_uncompressed_generates_two_segments PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ofh_uplane_packet_fragment_calculator.smaller_frame_size_than_prb_returns_zero_prbs /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter/ofh_uplane_packet_segment_calculator_test [==[--gtest_filter=ofh_uplane_packet_fragment_calculator.smaller_frame_size_than_prb_returns_zero_prbs]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_packet_fragment_calculator.smaller_frame_size_than_prb_returns_zero_prbs PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ofh_uplane_packet_fragment_calculator.segmented_packets_covers_whole_prb_range /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter/ofh_uplane_packet_segment_calculator_test [==[--gtest_filter=ofh_uplane_packet_fragment_calculator.segmented_packets_covers_whole_prb_range]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_packet_fragment_calculator.segmented_packets_covers_whole_prb_range PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ofh_uplane_packet_fragment_calculator.different_frame_size_segments /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter/ofh_uplane_packet_segment_calculator_test [==[--gtest_filter=ofh_uplane_packet_fragment_calculator.different_frame_size_segments]==] --gtest_also_run_disabled_tests)
set_tests_properties( ofh_uplane_packet_fragment_calculator.different_frame_size_segments PROPERTIES WORKING_DIRECTORY /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ofh/transmitter SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( ofh_uplane_packet_segment_calculator_test_TESTS ofh_uplane_packet_fragment_calculator.prbs_fit_in_one_segment_passes ofh_uplane_packet_fragment_calculator.whole_prb_range_compressed_passes ofh_uplane_packet_fragment_calculator.whole_prb_range_uncompressed_generates_two_segments ofh_uplane_packet_fragment_calculator.smaller_frame_size_than_prb_returns_zero_prbs ofh_uplane_packet_fragment_calculator.segmented_packets_covers_whole_prb_range ofh_uplane_packet_fragment_calculator.different_frame_size_segments)