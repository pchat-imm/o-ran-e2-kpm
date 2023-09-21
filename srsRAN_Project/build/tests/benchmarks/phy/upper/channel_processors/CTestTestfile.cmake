# CMake generated Testfile for 
# Source directory: /home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_processors
# Build directory: /home/oem/o-ran-e2/srsRAN_Project/build/tests/benchmarks/phy/upper/channel_processors
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pdsch_processor_benchmark "pdsch_processor_benchmark" "-m" "silent" "-R" "1" "-B" "1" "-T" "2" "-P" "pdsch_scs15_5MHz_qpsk_min" "-t" "concurrent")
set_tests_properties(pdsch_processor_benchmark PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_processors/CMakeLists.txt;34;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(prach_detector_benchmark "prach_detector_benchmark" "-R" "1")
set_tests_properties(prach_detector_benchmark PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_processors/CMakeLists.txt;44;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_processors/CMakeLists.txt;0;")
add_test(pusch_processor_benchmark "pusch_processor_benchmark" "-m" "silent" "-R" "1" "-B" "1" "-T" "2" "-P" "pusch_scs15_5MHz_qpsk_min")
set_tests_properties(pusch_processor_benchmark PROPERTIES  _BACKTRACE_TRIPLES "/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_processors/CMakeLists.txt;56;add_test;/home/oem/o-ran-e2/srsRAN_Project/tests/benchmarks/phy/upper/channel_processors/CMakeLists.txt;0;")
