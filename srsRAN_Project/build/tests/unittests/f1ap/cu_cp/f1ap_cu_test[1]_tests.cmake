add_test( f1ap_cu_ue_context_test.when_ue_added_then_ue_exists /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_test.when_ue_added_then_ue_exists]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_test.when_ue_added_then_ue_exists PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_test.when_ue_not_added_then_ue_doesnt_exist /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_test.when_ue_not_added_then_ue_doesnt_exist]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_test.when_ue_not_added_then_ue_doesnt_exist PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_test.when_unsupported_number_of_ues_addeded_then_ue_not_added /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_test.when_unsupported_number_of_ues_addeded_then_ue_not_added]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_test.when_unsupported_number_of_ues_addeded_then_ue_not_added PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_test.when_ue_exists_then_removal_succeeds /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_test.when_ue_exists_then_removal_succeeds]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_test.when_ue_exists_then_removal_succeeds PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_test.when_ue_is_added_then_next_ue_id_is_increased /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_test.when_ue_is_added_then_next_ue_id_is_increased]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_test.when_ue_is_added_then_next_ue_id_is_increased PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_test.when_next_ue_id_reaches_max_then_unused_values_are_reused /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_test.when_next_ue_id_reaches_max_then_unused_values_are_reused]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_test.when_next_ue_id_reaches_max_then_unused_values_are_reused PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_setup_test.when_request_sent_then_procedure_waits_for_response /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_setup_test.when_request_sent_then_procedure_waits_for_response]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_setup_test.when_request_sent_then_procedure_waits_for_response PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_setup_test.when_response_received_then_procedure_successful /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_setup_test.when_response_received_then_procedure_successful]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_setup_test.when_response_received_then_procedure_successful PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_setup_test.when_ue_setup_failure_received_then_procedure_unsuccessful /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_setup_test.when_ue_setup_failure_received_then_procedure_unsuccessful]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_setup_test.when_ue_setup_failure_received_then_procedure_unsuccessful PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_modification_test.when_f1ap_receives_response_then_procedure_completes /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_modification_test.when_f1ap_receives_response_then_procedure_completes]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_modification_test.when_f1ap_receives_response_then_procedure_completes PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_modification_test.when_f1ap_receives_response_with_failed_drb_then_it_forwards_the_failed_drb_outwards /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_modification_test.when_f1ap_receives_response_with_failed_drb_then_it_forwards_the_failed_drb_outwards]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_modification_test.when_f1ap_receives_response_with_failed_drb_then_it_forwards_the_failed_drb_outwards PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_ue_context_modification_test.when_ue_modification_failure_received_then_procedure_is_unsuccessful /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_ue_context_modification_test.when_ue_modification_failure_received_then_procedure_is_unsuccessful]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_ue_context_modification_test.when_ue_modification_failure_received_then_procedure_is_unsuccessful PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_ue_release_command_received_then_ue_removed /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_ue_release_command_received_then_ue_removed]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_ue_release_command_received_then_ue_removed PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_unsupported_f1ap_pdu_received_then_message_ignored /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_unsupported_f1ap_pdu_received_then_message_ignored]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_unsupported_f1ap_pdu_received_then_message_ignored PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_unsupported_init_msg_received_then_message_ignored /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_unsupported_init_msg_received_then_message_ignored]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_unsupported_init_msg_received_then_message_ignored PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_unsupported_successful_outcome_received_then_message_ignored /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_unsupported_successful_outcome_received_then_message_ignored]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_unsupported_successful_outcome_received_then_message_ignored PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_unsupported_unsuccessful_outcome_received_then_message_ignored /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_unsupported_unsuccessful_outcome_received_then_message_ignored]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_unsupported_unsuccessful_outcome_received_then_message_ignored PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_f1_setup_request_valid_then_connect_du /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_f1_setup_request_valid_then_connect_du]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_f1_setup_request_valid_then_connect_du PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_f1_setup_request_invalid_then_reject_du /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_f1_setup_request_invalid_then_reject_du]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_f1_setup_request_invalid_then_reject_du PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_init_ul_rrc_correct_then_ue_added /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_init_ul_rrc_correct_then_ue_added]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_init_ul_rrc_correct_then_ue_added PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_du_to_cu_rrc_container_missing_then_ue_not_added /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_du_to_cu_rrc_container_missing_then_ue_not_added]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_du_to_cu_rrc_container_missing_then_ue_not_added PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_max_nof_ues_PER_DU_exceeded_then_ue_not_added /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_max_nof_ues_PER_DU_exceeded_then_ue_not_added]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_max_nof_ues_PER_DU_exceeded_then_ue_not_added PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_ue_creation_fails_then_ue_not_added /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_ue_creation_fails_then_ue_not_added]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_ue_creation_fails_then_ue_not_added PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_rrc_setup_complete_present_then_forward_over_srb1 /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_rrc_setup_complete_present_then_forward_over_srb1]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_rrc_setup_complete_present_then_forward_over_srb1 PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_test.when_f1_removal_request_received_then_du_deleted /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_test.when_f1_removal_request_received_then_du_deleted]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_test.when_f1_removal_request_received_then_du_deleted PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_cu_msg_filler_test.when_context_mod_req_valid_then_valid_asn1_msg_generated /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_cu_msg_filler_test.when_context_mod_req_valid_then_valid_asn1_msg_generated]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_cu_msg_filler_test.when_context_mod_req_valid_then_valid_asn1_msg_generated PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
add_test( f1ap_paging_test.when_paging_message_received_message_is_forwarded /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp/f1ap_cu_test [==[--gtest_filter=f1ap_paging_test.when_paging_message_received_message_is_forwarded]==] --gtest_also_run_disabled_tests)
set_tests_properties( f1ap_paging_test.when_paging_message_received_message_is_forwarded PROPERTIES WORKING_DIRECTORY /home/oem/o-ran-e2/srsRAN_Project/build/tests/unittests/f1ap/cu_cp SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==] LABELS f1ap_cu)
set( f1ap_cu_test_TESTS f1ap_cu_ue_context_test.when_ue_added_then_ue_exists f1ap_cu_ue_context_test.when_ue_not_added_then_ue_doesnt_exist f1ap_cu_ue_context_test.when_unsupported_number_of_ues_addeded_then_ue_not_added f1ap_cu_ue_context_test.when_ue_exists_then_removal_succeeds f1ap_cu_ue_context_test.when_ue_is_added_then_next_ue_id_is_increased f1ap_cu_ue_context_test.when_next_ue_id_reaches_max_then_unused_values_are_reused f1ap_cu_ue_context_setup_test.when_request_sent_then_procedure_waits_for_response f1ap_cu_ue_context_setup_test.when_response_received_then_procedure_successful f1ap_cu_ue_context_setup_test.when_ue_setup_failure_received_then_procedure_unsuccessful f1ap_cu_ue_context_modification_test.when_f1ap_receives_response_then_procedure_completes f1ap_cu_ue_context_modification_test.when_f1ap_receives_response_with_failed_drb_then_it_forwards_the_failed_drb_outwards f1ap_cu_ue_context_modification_test.when_ue_modification_failure_received_then_procedure_is_unsuccessful f1ap_cu_test.when_ue_release_command_received_then_ue_removed f1ap_cu_test.when_unsupported_f1ap_pdu_received_then_message_ignored f1ap_cu_test.when_unsupported_init_msg_received_then_message_ignored f1ap_cu_test.when_unsupported_successful_outcome_received_then_message_ignored f1ap_cu_test.when_unsupported_unsuccessful_outcome_received_then_message_ignored f1ap_cu_test.when_f1_setup_request_valid_then_connect_du f1ap_cu_test.when_f1_setup_request_invalid_then_reject_du f1ap_cu_test.when_init_ul_rrc_correct_then_ue_added f1ap_cu_test.when_du_to_cu_rrc_container_missing_then_ue_not_added f1ap_cu_test.when_max_nof_ues_PER_DU_exceeded_then_ue_not_added f1ap_cu_test.when_ue_creation_fails_then_ue_not_added f1ap_cu_test.when_rrc_setup_complete_present_then_forward_over_srb1 f1ap_cu_test.when_f1_removal_request_received_then_du_deleted f1ap_cu_msg_filler_test.when_context_mod_req_valid_then_valid_asn1_msg_generated f1ap_paging_test.when_paging_message_received_message_is_forwarded)