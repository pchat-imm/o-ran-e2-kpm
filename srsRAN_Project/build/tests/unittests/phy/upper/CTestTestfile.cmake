# CMake generated Testfile for 
# Source directory: /home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper
# Build directory: /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper/downlink_processor_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper/hard_decision_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper/uplink_processor_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper/uplink_request_processor_test[1]_include.cmake")
include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/phy/upper/upper_phy_rx_symbol_handler_test[1]_include.cmake")
add_test(downlink_processor_pool_test "downlink_processor_pool_test")
set_tests_properties(downlink_processor_pool_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper/CMakeLists.txt;35;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper/CMakeLists.txt;0;")
add_test(log_likelihood_ratio_test "log_likelihood_ratio_test")
set_tests_properties(log_likelihood_ratio_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper/CMakeLists.txt;47;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper/CMakeLists.txt;0;")
add_test(rx_softbuffer_pool_test "rx_softbuffer_pool_test")
set_tests_properties(rx_softbuffer_pool_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper/CMakeLists.txt;51;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper/CMakeLists.txt;0;")
add_test(vrb_to_prb_mapper_test "vrb_to_prb_mapper_test")
set_tests_properties(vrb_to_prb_mapper_test PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper/CMakeLists.txt;67;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/unittests/phy/upper/CMakeLists.txt;0;")
subdirs("channel_coding")
subdirs("channel_modulation")
subdirs("channel_processors")
subdirs("equalization")
subdirs("sequence_generators")
subdirs("signal_processors")
set_directory_properties(PROPERTIES LABELS "phy")
