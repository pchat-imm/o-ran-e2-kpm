if(EXISTS "/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/ofh/serdes/ofh_uplane_packet_decoder_dynamic_impl[1]_tests.cmake")
  include("/home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/ofh/serdes/ofh_uplane_packet_decoder_dynamic_impl[1]_tests.cmake")
else()
  add_test(ofh_uplane_packet_decoder_dynamic_impl_NOT_BUILT ofh_uplane_packet_decoder_dynamic_impl_NOT_BUILT)
endif()