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

#include "srsran/ofh/ethernet/ethernet_gateway.h"
#include "srsran/srslog/logger.h"

struct rte_mempool;

namespace srsran {
namespace ether {

struct gw_config;

/// DPDK Ethernet transmitter implementation.
class dpdk_transmitter_impl : public gateway
{
public:
  explicit dpdk_transmitter_impl(const gw_config& config, srslog::basic_logger& logger_);

  // See interface for documentation.
  void send(span<span<const uint8_t>> frames) override;

private:
  srslog::basic_logger& logger;
  const unsigned        port_id   = 0;
  ::rte_mempool*        mbuf_pool = nullptr;
};

} // namespace ether
} // namespace srsran
