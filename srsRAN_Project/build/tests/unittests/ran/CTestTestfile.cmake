# CMake generated Testfile for 
# Source directory: /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran
# Build directory: /home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/csi_report_on_pucch_helpers_test[1]_include.cmake")
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/csi_report_on_pucch_validator_test[1]_include.cmake")
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/csi_report_on_pusch_helpers_test[1]_include.cmake")
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/csi_report_on_pusch_validator_test[1]_include.cmake")
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/bcd_helpers_test[1]_include.cmake")
include("/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/build/tests/unittests/ran/nr_cgi_helpers_test[1]_include.cmake")
add_test(test_ssb_coreset0_freq_pos_generator "test_ssb_coreset0_freq_pos_generator")
set_tests_properties(test_ssb_coreset0_freq_pos_generator PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;46;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(dci_packing_test "dci_packing_test")
set_tests_properties(dci_packing_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;50;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(dci_packing_validator_test "dci_packing_validator_test")
set_tests_properties(dci_packing_validator_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;54;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(pdcch_candidates_common "pdcch_candidates_common")
set_tests_properties(pdcch_candidates_common PROPERTIES  LABELS "vectortest" _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/CMakeLists.txt;48;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;58;add_test_vector;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(pdcch_candidates_ue "pdcch_candidates_ue")
set_tests_properties(pdcch_candidates_ue PROPERTIES  LABELS "vectortest" _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/CMakeLists.txt;48;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;62;add_test_vector;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(pdcch_type0_css_coreset_config_test "pdcch_type0_css_coreset_config_test")
set_tests_properties(pdcch_type0_css_coreset_config_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;66;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(pdsch_mcs_table_test "pdsch_mcs_table_test")
set_tests_properties(pdsch_mcs_table_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;70;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(prach_configuration_test "prach_configuration_test")
set_tests_properties(prach_configuration_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;74;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(prach_cyclic_shifts_test "prach_cyclic_shifts_test")
set_tests_properties(prach_cyclic_shifts_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;78;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(prach_frequency_mapping_test "prach_frequency_mapping_test")
set_tests_properties(prach_frequency_mapping_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;82;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(pucch_info_test "pucch_info_test")
set_tests_properties(pucch_info_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;86;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(pusch_mcs_table_test "pusch_mcs_table_test")
set_tests_properties(pusch_mcs_table_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;90;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(ulsch_info_test "ulsch_info_test")
set_tests_properties(ulsch_info_test PROPERTIES  LABELS "vectortest" _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/CMakeLists.txt;48;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;94;add_test_vector;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(resource_allocation_frequency_test "resource_allocation_frequency_test")
set_tests_properties(resource_allocation_frequency_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;98;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(uci_part2_size_calculator_test "uci_part2_size_calculator_test")
set_tests_properties(uci_part2_size_calculator_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;102;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(slot_point_test "slot_point_test")
set_tests_properties(slot_point_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;106;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(band_helper_test "band_helper_test")
set_tests_properties(band_helper_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;111;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(ssb_gscn_test "ssb_gscn_test")
set_tests_properties(ssb_gscn_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;115;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
add_test(ssb_mapping_test "ssb_mapping_test")
set_tests_properties(ssb_mapping_test PROPERTIES  _BACKTRACE_TRIPLES "/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;119;add_test;/home/chatchamon/o-ran-e2-kpm/srsRAN_Project/tests/unittests/ran/CMakeLists.txt;0;")
set_directory_properties(PROPERTIES LABELS "ran")