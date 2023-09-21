# CMake generated Testfile for 
# Source directory: /home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_coding/ldpc
# Build directory: /home/oem/o-ran-e2/srsRAN_Project/build/tests/benchmarks/phy/upper/channel_coding/ldpc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ldpc_encoder_benchmark "ldpc_encoder_benchmark" "-s" "-R" "1" "-T" "generic")
set_tests_properties(ldpc_encoder_benchmark PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_coding/ldpc/CMakeLists.txt;23;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_coding/ldpc/CMakeLists.txt;0;")
add_test(ldpc_decoder_benchmark "ldpc_decoder_benchmark" "-s" "-R" "1" "-I" "2" "-T" "generic")
set_tests_properties(ldpc_decoder_benchmark PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_coding/ldpc/CMakeLists.txt;27;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_coding/ldpc/CMakeLists.txt;0;")
