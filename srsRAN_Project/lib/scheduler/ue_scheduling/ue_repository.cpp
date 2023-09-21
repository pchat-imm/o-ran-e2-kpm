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

#include "ue_repository.h"

using namespace srsran;

ue_repository::ue_repository(sched_configuration_notifier& mac_notif_) :
  mac_notif(mac_notif_), logger(srslog::fetch_basic_logger("SCHED"))
{
}

/// \brief This function checks whether it is safe to remove a UE. Currently we verify that:
/// - The UE has no pending DL SRB data. This ensures that messages like RRC Release are sent before the UE removal.
/// - The UE has no DL or UL HARQ awaiting an ACK.
static bool is_ue_ready_for_removal(ue& u)
{
  // Ensure that there no currently active HARQs.
  unsigned nof_ue_cells = u.nof_cells();
  for (unsigned cell_idx = 0; cell_idx != nof_ue_cells; ++cell_idx) {
    ue_cell& c = u.get_cell((ue_cell_index_t)cell_idx);
    for (unsigned i = 0; i != c.harqs.nof_dl_harqs(); ++i) {
      if (not c.harqs.dl_harq(i).empty()) {
        return false;
      }
    }
    for (unsigned i = 0; i != c.harqs.nof_ul_harqs(); ++i) {
      if (not c.harqs.ul_harq(i).empty()) {
        return false;
      }
    }
  }

  return true;
}

void ue_repository::slot_indication(slot_point sl_tx)
{
  for (du_ue_index_t& ue_index : ues_to_rem) {
    if (ue_index == INVALID_DU_UE_INDEX) {
      // Already removed.
      continue;
    }
    if (not ues.contains(ue_index)) {
      logger.warning("Unexpected removal of ue={} already took place", ue_index);
      ue_index = INVALID_DU_UE_INDEX;
      // Notify MAC of the successful UE removal.
      mac_notif.on_ue_delete_response(ue_index);
      continue;
    }
    ue& u = *ues[ue_index];

    // Check if UEs can be safely removed.
    if (is_ue_ready_for_removal(u)) {
      logger.debug("ue={} has been successfully removed.", ue_index);

      // Notify MAC of the successful UE removal.
      mac_notif.on_ue_delete_response(ue_index);

      // Remove UE from the repository.
      ues.erase(ue_index);

      // Mark UE as ready for removal.
      ue_index = INVALID_DU_UE_INDEX;
    }
  }

  // In case the elements at the front of the ring has been marked for removal, pop them from the queue.
  while (not ues_to_rem.empty() and ues_to_rem[0] == INVALID_DU_UE_INDEX) {
    ues_to_rem.pop();
  }

  // Update state of existing UEs.
  for (auto& u : ues) {
    u->slot_indication(sl_tx);
  }
}

void ue_repository::add_ue(std::unique_ptr<ue> u)
{
  du_ue_index_t ue_index = u->ue_index;
  ues.insert(ue_index, std::move(u));
}

void ue_repository::schedule_ue_rem(du_ue_index_t ue_index)
{
  if (contains(ue_index)) {
    // Start deactivation of UE bearers.
    ues[ue_index]->deactivate();

    // Register UE for later removal.
    ues_to_rem.push(ue_index);
  }
}
