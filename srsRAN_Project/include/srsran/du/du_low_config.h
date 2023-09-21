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

#include "srsran/phy/upper/upper_phy_factories.h"

namespace srsran {

/// Parameters used to instantiate the DU-low.
struct du_low_configuration {
  /// Logger used to report state of the DU-low.
  srslog::basic_logger* logger;
  /// Parameters forwarded to DL processor factory.
  downlink_processor_factory_sw_config dl_proc_cfg;
  /// Upper PHY configuration.
  std::vector<upper_phy_config> upper_phy;
};

} // namespace srsran