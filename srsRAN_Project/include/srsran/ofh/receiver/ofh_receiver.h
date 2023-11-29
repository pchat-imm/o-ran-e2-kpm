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

#include "srsran/ofh/ethernet/ethernet_frame_notifier.h"
#include "srsran/ofh/ofh_ota_symbol_handler.h"

namespace srsran {
namespace ofh {

/// Open Fronthaul receiver interface.
class receiver
{
public:
  virtual ~receiver() = default;

  /// Returns the ethernet_frame_notifier of this Open Fronthaul receiver.
  virtual ether::frame_notifier& get_ethernet_frame_notifier() = 0;

  /// Returns the OTA symbol handler of this Open Fronthaul receiver.
  virtual ota_symbol_handler& get_ota_symbol_handler() = 0;
};

} // namespace ofh
} // namespace srsran
