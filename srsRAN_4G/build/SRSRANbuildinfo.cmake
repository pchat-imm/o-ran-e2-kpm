
execute_process(
COMMAND git rev-parse --abbrev-ref HEAD
WORKING_DIRECTORY "/home/oem/o-ran-e2/srsRAN_4G"
OUTPUT_VARIABLE GIT_BRANCH
OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
COMMAND git log -1 --format=%h
WORKING_DIRECTORY "/home/oem/o-ran-e2/srsRAN_4G"
OUTPUT_VARIABLE GIT_COMMIT_HASH
OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Generating build_info.h")
configure_file(
  /home/oem/o-ran-e2/srsRAN_4G/lib/include/srsran/build_info.h.in
  /home/oem/o-ran-e2/srsRAN_4G/build/lib/include/srsran/build_info.h
)
