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

#pragma once

#include "srsran/cu_cp/mobility_manager.h"

namespace srsran {
namespace srs_cu_cp {

/// Basic cell manager implementation
class mobility_manager_impl final : public mobility_manager
{
public:
  mobility_manager_impl(const mobility_manager_cfg& cfg, du_repository& du_db_, du_processor_ue_manager& ue_mng_);
  ~mobility_manager_impl() = default;

  void handle_neighbor_better_than_spcell(ue_index_t ue_index, pci_t neighbor_pci) override;

private:
  void handle_inter_cu_handover(ue_index_t source_ue_index, pci_t neighbor_pci);
  void handle_inter_du_handover(ue_index_t source_ue_index,
                                pci_t      neighbor_pci,
                                du_index_t source_du_index,
                                du_index_t target_du_index);
  void handle_intra_du_handover(ue_index_t source_ue_index, pci_t neighbor_pci);

  mobility_manager_cfg cfg;

  du_repository&           du_db;
  du_processor_ue_manager& ue_mng;

  srslog::basic_logger& logger;
};

} // namespace srs_cu_cp
} // namespace srsran
