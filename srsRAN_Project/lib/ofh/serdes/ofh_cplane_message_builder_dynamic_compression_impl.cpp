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

#include "ofh_cplane_message_builder_dynamic_compression_impl.h"
#include "../support/network_order_binary_serializer.h"

using namespace srsran;
using namespace ofh;

void cplane_message_builder_dynamic_compression_impl::serialize_compression_header(
    network_order_binary_serializer& serializer,
    const ru_compression_params&     compr,
    data_direction                   direction) const
{
  // Downlink always encodes a 0.
  if (direction == data_direction::downlink) {
    static constexpr uint8_t reserved = 0;
    serializer.write(reserved);

    return;
  }

  uint8_t value = 0;
  value |= uint8_t(compr.data_width) << 4;
  value |= uint8_t(to_value(compr.type));

  serializer.write(value);
}
