if(KPM_VERSION STREQUAL "KPM_V2")
  set(KPM_SRC ../../src/sm/kpm_sm/kpm_sm_v02.03/ie/kpm_data_ie.c)
  set(KPM_ASN_DIR  "../../src/sm/kpm_sm/kpm_sm_v02.03/ie/asn")
elseif(KPM_VERSION STREQUAL "KPM_V3")
  set(KPM_SRC ../../src/sm/kpm_sm/kpm_sm_v03.00/ie/kpm_data_ie.c)
  set(KPM_ASN_DIR  "../../src/sm/kpm_sm/kpm_sm_v03.00/ie/asn")
else()
  message(FATAL_ERROR "Unknown KPM version")
endif()



#############################
# E2E Test E2-AGENT NEAR-RIC 
#############################

add_executable(test_near_ric 
  test_near_ric.c 
  ../rnd/fill_rnd_data_gtp.c  
  ../rnd/fill_rnd_data_tc.c                  
  ../rnd/fill_rnd_data_mac.c  
  ../rnd/fill_rnd_data_rlc.c 
  ../rnd/fill_rnd_data_pdcp.c
  ../rnd/fill_rnd_data_kpm.c
  ../rnd/fill_rnd_data_rc.c                  
  ../rnd/fill_rnd_data_slice.c 
  ../rnd/fill_rnd_data_e2_setup_req.c 
  ${KPM_SRC} 
  ../../src/sm/rc_sm/ie/rc_data_ie.c
  ../../src/util/conversions.c
  )

target_link_libraries(test_near_ric
                      PUBLIC 
                      e2_agent
                      ${FlatCC}
                      kpm_sm
                      #/home/mir/workspace/flatcc/lib/libflatccrt_d.a
                      $<TARGET_OBJECTS:kpm_ric_info_common_obj>
                      $<TARGET_OBJECTS:kpm_ric_info_obj>
                      $<TARGET_OBJECTS:e2sm_common_ie_obj>
                      $<TARGET_OBJECTS:3gpp_common_ie_obj>
                      $<TARGET_OBJECTS:e2sm_common_ie_obj>
                      $<TARGET_OBJECTS:e2sm_rc_ir_obj>
                      near_ric_test
                      -pthread
                      -lsctp
                      -ldl)

target_compile_options(test_near_ric PUBLIC "-DASN_DISABLE_JER_SUPPORT" "-DASN_DISABLE_OER_SUPPORT")
target_include_directories(test_near_ric PRIVATE ${KPM_ASN_DIR} )

