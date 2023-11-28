/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "inter_du_handover_routine.h"
#include "../pdu_session_routine_helpers.h"
#include "handover_reconfiguration_routine.h"
#include "mobility_helpers.h"
#include "srsran/cu_cp/cu_cp_types.h"

using namespace srsran;
using namespace srsran::srs_cu_cp;
using namespace asn1::rrc_nr;

inter_du_handover_routine::inter_du_handover_routine(
    const cu_cp_inter_du_handover_request&        command_,
    du_processor_cu_cp_notifier&                  cu_cp_notifier_,
    du_processor_f1ap_ue_context_notifier&        source_du_f1ap_ue_ctxt_notif_,
    du_processor_f1ap_ue_context_notifier&        target_du_f1ap_ue_ctxt_notif_,
    du_processor_e1ap_control_notifier&           e1ap_ctrl_notif_,
    du_processor_ue_manager&                      ue_manager_,
    du_processor_rrc_ue_control_message_notifier& rrc_ue_ctrl_notifier_,
    up_resource_manager&                          ue_up_resource_manager_,
    srslog::basic_logger&                         logger_) :
  command(command_),
  cu_cp_notifier(cu_cp_notifier_),
  source_du_f1ap_ue_ctxt_notifier(source_du_f1ap_ue_ctxt_notif_),
  target_du_f1ap_ue_ctxt_notifier(target_du_f1ap_ue_ctxt_notif_),
  e1ap_ctrl_notifier(e1ap_ctrl_notif_),
  ue_manager(ue_manager_),
  rrc_ue_ctrl_notifier(rrc_ue_ctrl_notifier_),
  ue_up_resource_manager(ue_up_resource_manager_),
  logger(logger_)
{
  source_ue = ue_manager.find_du_ue(command.source_ue_index);
  srsran_assert(source_ue != nullptr, "Can't find source UE index {}.", command.source_ue_index);

  next_config = to_config_update(ue_up_resource_manager.get_up_context());
}

void inter_du_handover_routine::operator()(coro_context<async_task<cu_cp_inter_du_handover_response>>& ctx)
{
  CORO_BEGIN(ctx);

  logger.debug("ue={}: \"{}\" initialized.", command.source_ue_index, name());

  {
    // Allocate UE index at target DU
    target_ue_context_setup_request.ue_index = ue_manager.allocate_new_ue_index(command.target_du_index);
    if (target_ue_context_setup_request.ue_index == ue_index_t::invalid) {
      logger.error("ue={}: \"{}\" failed to allocate UE index at target DU.", command.source_ue_index, name());
      CORO_EARLY_RETURN(response_msg);
    }

    // prepare F1AP UE Context Setup Command and call F1AP notifier of target DU
    if (!generate_ue_context_setup_request(target_ue_context_setup_request,
                                           source_ue->get_rrc_ue_srb_notifier().get_srbs())) {
      logger.error("ue={}: \"{}\" failed to generate UE context setup request at DU.", command.source_ue_index, name());
      CORO_EARLY_RETURN(response_msg);
    }

    CORO_AWAIT_VALUE(target_ue_context_setup_response,
                     target_du_f1ap_ue_ctxt_notifier.on_ue_context_setup_request(target_ue_context_setup_request));

    // Handle UE Context Setup Response
    if (!handle_context_setup_response(
            response_msg, bearer_context_modification_request, target_ue_context_setup_response, next_config, logger)) {
      logger.error("ue={}: \"{}\" failed to create UE context at target DU.", command.source_ue_index, name());
      cu_cp_notifier.on_ue_removal_required(target_ue_context_setup_request.ue_index);
      CORO_EARLY_RETURN(response_msg);
    }
  }

  // Target UE object exists from this point on.
  target_ue = ue_manager.find_du_ue(target_ue_context_setup_response.ue_index);
  srsran_assert(
      target_ue != nullptr, "Couldn't find UE with index {} in target DU", target_ue_context_setup_response.ue_index);

  // Setup SRB1 and initialize security context in RRC
  {
    create_srb1(target_ue);
#if 0
    if (!ue->get_rrc_ue_notifier().on_new_security_context(request.security_context)) {
      logger.error("ue={}: \"{}\" failed to setup security context at UE.", request.ue_index, name());
      CORO_EARLY_RETURN(response_msg);
    }
#endif
  }

  // Inform CU-UP about new DL tunnels.
  {
    //  prepare Bearer Context Release Command and call E1AP notifier
    bearer_context_modification_request.ue_index = command.source_ue_index;

    // call E1AP procedure and wait for BearerContextModificationResponse
    CORO_AWAIT_VALUE(bearer_context_modification_response,
                     e1ap_ctrl_notifier.on_bearer_context_modification_request(bearer_context_modification_request));

    // Handle Bearer Context Modification Response
    if (!handle_bearer_context_modification_response(
            response_msg, source_ue_context_mod_request, bearer_context_modification_response, next_config, logger)) {
      logger.error("ue={}: \"{}\" failed to modify bearer context at target CU-UP.", command.source_ue_index, name());

      {
        ue_context_release_cmd.ue_index = target_ue_context_setup_response.ue_index;
        ue_context_release_cmd.cause    = cause_radio_network_t::unspecified;
        CORO_AWAIT_VALUE(ue_context_release_result,
                         target_du_f1ap_ue_ctxt_notifier.on_ue_context_release_command(ue_context_release_cmd));

        if (ue_context_release_result == ue_index_t::invalid) {
          logger.error("ue={}: \"{}\" failed to remove UE context at target DU.", command.source_ue_index, name());
        } else {
          logger.debug("ue={}: \"{}\" removed UE context for {} at target DU.",
                       command.source_ue_index,
                       name(),
                       ue_context_release_result);
        }
      }

      CORO_EARLY_RETURN(response_msg);
    }
  }

  {
    // prepare RRC Reconfiguration and call RRC UE notifier
    // if default DRB is being setup, SRB2 needs to be setup as well
    {
      fill_rrc_reconfig_args(rrc_reconfig_args,
                             target_ue_context_setup_request.srbs_to_be_setup_list,
                             next_config.pdu_sessions_to_setup_list,
                             target_ue_context_setup_response.du_to_cu_rrc_info,
                             {} /* No NAS PDUs required */,
                             target_ue->get_rrc_ue_notifier().get_rrc_ue_meas_config(),
                             true, /* Reestablish SRBs */
                             false /* do not reestablish DRBs */);
    }

    target_ue = ue_manager.find_du_ue(target_ue_context_setup_response.ue_index);
    // Trigger RRC Reconfiguration
    CORO_AWAIT_VALUE(bool reconf_result,
                     launch_async<handover_reconfiguration_routine>(rrc_reconfig_args, *source_ue, *target_ue, logger));

    if (!reconf_result) {
      logger.error("ue={}: \"{}\" RRC Reconfiguration failed.", command.source_ue_index, name());
      CORO_EARLY_RETURN(response_msg);
    }
  }

  // Remove UE context in source DU.
  {
    ue_context_release_cmd.ue_index = source_ue->get_ue_index();
    ue_context_release_cmd.cause    = cause_radio_network_t::unspecified;
    CORO_AWAIT_VALUE(ue_context_release_result,
                     source_du_f1ap_ue_ctxt_notifier.on_ue_context_release_command(ue_context_release_cmd));

    if (ue_context_release_result == ue_index_t::invalid) {
      logger.error("ue={}: \"{}\" failed to remove UE context at source DU.", command.source_ue_index, name());
    } else {
      logger.debug("ue={}: \"{}\" removed UE context for {} at source DU.",
                   command.source_ue_index,
                   name(),
                   ue_context_release_result);
    }
  }

  CORO_RETURN(response_msg);
}

bool inter_du_handover_routine::generate_ue_context_setup_request(f1ap_ue_context_setup_request& setup_request,
                                                                  const static_vector<srb_id_t, MAX_NOF_SRBS>& srbs)
{
  setup_request.serv_cell_idx = 0; // TODO: Remove hardcoded value
  setup_request.sp_cell_id    = command.cgi;
  setup_request.cu_to_du_rrc_info.ie_exts.emplace();
  setup_request.cu_to_du_rrc_info.ie_exts.value().ho_prep_info =
      rrc_ue_ctrl_notifier.get_packed_handover_preparation_message();

  for (const auto& srb_id : srbs) {
    f1ap_srbs_to_be_setup_mod_item srb_item;
    srb_item.srb_id = srb_id;
    setup_request.srbs_to_be_setup_list.emplace(srb_item.srb_id, srb_item);
  }

  for (const auto& pdu_session : next_config.pdu_sessions_to_setup_list) {
    for (const auto& drb : pdu_session.second.drb_to_add) {
      const up_drb_context& drb_context = drb.second;

      f1ap_drbs_to_be_setup_mod_item drb_item;
      drb_item.drb_id           = drb_context.drb_id;
      drb_item.qos_info.drb_qos = drb_context.qos_params;

      // Add each QoS flow including QoS.
      for (auto& flow : drb_context.qos_flows) {
        f1ap_flows_mapped_to_drb_item flow_item;
        flow_item.qos_flow_id               = flow.first;
        flow_item.qos_flow_level_qos_params = flow.second.qos_params;
        drb_item.qos_info.flows_mapped_to_drb_list.emplace(flow_item.qos_flow_id, flow_item);
      }
      drb_item.ul_up_tnl_info_to_be_setup_list = drb_context.ul_up_tnl_info_to_be_setup_list;
      drb_item.rlc_mod                         = drb_context.rlc_mod;

      setup_request.drbs_to_be_setup_list.emplace(drb_item.drb_id, drb_item);
    }
  }

  return true;
}

void inter_du_handover_routine::create_srb1(du_ue* ue)
{
  // create SRB1
  srb_creation_message srb1_msg{};
  srb1_msg.ue_index = ue->get_ue_index();
  srb1_msg.srb_id   = srb_id_t::srb1;
  srb1_msg.pdcp_cfg = asn1::rrc_nr::pdcp_cfg_s{};
  ue->get_rrc_ue_srb_notifier().create_srb(srb1_msg);
}