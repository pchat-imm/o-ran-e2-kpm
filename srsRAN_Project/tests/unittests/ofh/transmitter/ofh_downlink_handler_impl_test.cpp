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

#include "../../../../lib/ofh/transmitter/ofh_data_flow_uplane_downlink_data.h"
#include "../../../../lib/ofh/transmitter/ofh_downlink_handler_impl.h"
#include "ofh_data_flow_cplane_scheduling_commands_test_doubles.h"
#include "srsran/phy/support/resource_grid_context.h"
#include "srsran/phy/support/resource_grid_reader_empty.h"
#include <gtest/gtest.h>

using namespace srsran;
using namespace ofh;
using namespace srsran::ofh::testing;

namespace {

/// Spy User-Plane downlink data data flow.
class data_flow_uplane_downlink_data_spy : public data_flow_uplane_downlink_data
{
  bool     has_enqueue_section_type_1_message_method_been_called = false;
  unsigned eaxc                                                  = -1;

public:
  // See interface for documentation.
  void enqueue_section_type_1_message(const data_flow_uplane_resource_grid_context& context,
                                      const resource_grid_reader&                   grid) override
  {
    has_enqueue_section_type_1_message_method_been_called = true;
    eaxc                                                  = context.eaxc;
  }

  /// Returns true if the method enqueue section type 1 message has been called, otherwise false.
  bool has_enqueue_section_type_1_method_been_called() const
  {
    return has_enqueue_section_type_1_message_method_been_called;
  }

  /// Returns the configured eAxC.
  unsigned get_eaxc() const { return eaxc; }
};

} // namespace

TEST(ofh_downlink_handler_impl, handling_downlink_data_use_control_and_user_plane)
{
  downlink_handler_impl_config config;
  config.dl_eaxc = {24};

  unsigned nof_symbols            = 14;
  unsigned numerlogy              = to_numerology_value(subcarrier_spacing::kHz30);
  unsigned nof_symbols_before_ota = 14;

  downlink_handler_impl_dependencies dependencies;
  dependencies.logger = &srslog::fetch_basic_logger("TEST");
  std::unique_ptr<data_flow_cplane_scheduling_commands_spy> cplane =
      std::make_unique<data_flow_cplane_scheduling_commands_spy>();
  const auto& cplane_spy                                     = *cplane;
  dependencies.data_flow_cplane                              = std::move(cplane);
  std::unique_ptr<data_flow_uplane_downlink_data_spy> uplane = std::make_unique<data_flow_uplane_downlink_data_spy>();
  const auto&                                         uplane_spy = *uplane;
  dependencies.data_flow_uplane                                  = std::move(uplane);
  dependencies.window_checker =
      std::make_unique<tx_window_checker>(*dependencies.logger, nof_symbols_before_ota, nof_symbols, numerlogy);
  dependencies.frame_pool_ptr = std::make_shared<ether::eth_frame_pool>();

  auto& window_checker = *dependencies.window_checker;

  downlink_handler_impl handler(config, std::move(dependencies));

  resource_grid_reader_empty rg(1, 1, 1);
  resource_grid_context      rg_context;
  rg_context.slot   = slot_point(1, 1, 1);
  rg_context.sector = 1;

  // Set the OTA to the same slot as the grid.
  slot_symbol_point ota_time(rg_context.slot, 0, nof_symbols);

  // Delay the OTA 3 slots.
  ota_time -= (3 * nof_symbols);
  window_checker.handle_new_ota_symbol(ota_time);

  handler.handle_dl_data(rg_context, rg);

  // Assert Control-Plane.
  ASSERT_TRUE(cplane_spy.has_enqueue_section_type_1_method_been_called());
  const data_flow_cplane_scheduling_commands_spy::spy_info& info = cplane_spy.get_spy_info();
  ASSERT_EQ(rg_context.slot, info.slot);
  ASSERT_EQ(config.dl_eaxc[0], info.eaxc);
  ASSERT_EQ(data_direction::downlink, info.direction);
  ASSERT_EQ(filter_index_type::standard_channel_filter, info.filter_type);

  // Assert User-Plane.
  ASSERT_TRUE(uplane_spy.has_enqueue_section_type_1_method_been_called());
  ASSERT_EQ(config.dl_eaxc[0], uplane_spy.get_eaxc());
}

TEST(ofh_downlink_handler_impl, late_rg_is_not_handled)
{
  downlink_handler_impl_config config;
  config.dl_eaxc = {24};

  unsigned nof_symbols            = 14;
  unsigned numerlogy              = to_numerology_value(subcarrier_spacing::kHz30);
  unsigned nof_symbols_before_ota = 14;

  downlink_handler_impl_dependencies dependencies;
  dependencies.logger = &srslog::fetch_basic_logger("TEST");
  std::unique_ptr<data_flow_cplane_scheduling_commands_spy> cplane =
      std::make_unique<data_flow_cplane_scheduling_commands_spy>();
  const auto& cplane_spy                                     = *cplane;
  dependencies.data_flow_cplane                              = std::move(cplane);
  std::unique_ptr<data_flow_uplane_downlink_data_spy> uplane = std::make_unique<data_flow_uplane_downlink_data_spy>();
  const auto&                                         uplane_spy = *uplane;
  dependencies.data_flow_uplane                                  = std::move(uplane);
  dependencies.window_checker =
      std::make_unique<tx_window_checker>(*dependencies.logger, nof_symbols_before_ota, nof_symbols, numerlogy);
  dependencies.frame_pool_ptr = std::make_shared<ether::eth_frame_pool>();

  auto& window_checker = *dependencies.window_checker;

  downlink_handler_impl handler(config, std::move(dependencies));

  resource_grid_reader_empty rg(1, 1, 1);
  resource_grid_context      rg_context;
  rg_context.slot   = slot_point(1, 1, 1);
  rg_context.sector = 1;

  // Set the OTA to the same slot as the grid.
  slot_symbol_point ota_time(rg_context.slot, 0, nof_symbols);

  // Delay the OTA, as the grid should always be advanced in slot.
  ota_time -= nof_symbols;

  window_checker.handle_new_ota_symbol(ota_time);

  handler.handle_dl_data(rg_context, rg);

  // Assert Control-Plane.
  ASSERT_FALSE(cplane_spy.has_enqueue_section_type_1_method_been_called());
  ASSERT_FALSE(uplane_spy.has_enqueue_section_type_1_method_been_called());
}

TEST(ofh_downlink_handler_impl, same_slot_fails)
{
  downlink_handler_impl_config config;
  config.dl_eaxc = {24};

  unsigned nof_symbols            = 14;
  unsigned numerlogy              = to_numerology_value(subcarrier_spacing::kHz30);
  unsigned nof_symbols_before_ota = 14;

  downlink_handler_impl_dependencies dependencies;
  dependencies.logger = &srslog::fetch_basic_logger("TEST");
  std::unique_ptr<data_flow_cplane_scheduling_commands_spy> cplane =
      std::make_unique<data_flow_cplane_scheduling_commands_spy>();
  const auto& cplane_spy                                     = *cplane;
  dependencies.data_flow_cplane                              = std::move(cplane);
  std::unique_ptr<data_flow_uplane_downlink_data_spy> uplane = std::make_unique<data_flow_uplane_downlink_data_spy>();
  const auto&                                         uplane_spy = *uplane;
  dependencies.data_flow_uplane                                  = std::move(uplane);
  dependencies.window_checker =
      std::make_unique<tx_window_checker>(*dependencies.logger, nof_symbols_before_ota, nof_symbols, numerlogy);
  dependencies.frame_pool_ptr = std::make_shared<ether::eth_frame_pool>();

  auto& window_checker = *dependencies.window_checker;

  downlink_handler_impl handler(config, std::move(dependencies));

  resource_grid_reader_empty rg(1, 1, 1);
  resource_grid_context      rg_context;
  rg_context.slot   = slot_point(1, 1, 1);
  rg_context.sector = 1;

  // Set the OTA to the same slot as the grid.
  slot_symbol_point ota_time(rg_context.slot, 0, nof_symbols);
  // Same slot and symbol than the resource grid.
  window_checker.handle_new_ota_symbol(ota_time);

  handler.handle_dl_data(rg_context, rg);

  // Assert Control-Plane.
  ASSERT_FALSE(cplane_spy.has_enqueue_section_type_1_method_been_called());
  ASSERT_FALSE(uplane_spy.has_enqueue_section_type_1_method_been_called());
}

TEST(ofh_downlink_handler_impl, rg_in_the_frontier_is_handled)
{
  downlink_handler_impl_config config;
  config.dl_eaxc = {24};

  unsigned nof_symbols            = 14;
  unsigned numerlogy              = to_numerology_value(subcarrier_spacing::kHz30);
  unsigned nof_symbols_before_ota = 14;

  downlink_handler_impl_dependencies dependencies;
  dependencies.logger = &srslog::fetch_basic_logger("TEST");
  std::unique_ptr<data_flow_cplane_scheduling_commands_spy> cplane =
      std::make_unique<data_flow_cplane_scheduling_commands_spy>();
  const auto& cplane_spy                                     = *cplane;
  dependencies.data_flow_cplane                              = std::move(cplane);
  std::unique_ptr<data_flow_uplane_downlink_data_spy> uplane = std::make_unique<data_flow_uplane_downlink_data_spy>();
  const auto&                                         uplane_spy = *uplane;
  dependencies.data_flow_uplane                                  = std::move(uplane);
  dependencies.window_checker =
      std::make_unique<tx_window_checker>(*dependencies.logger, nof_symbols_before_ota, nof_symbols, numerlogy);
  dependencies.frame_pool_ptr = std::make_shared<ether::eth_frame_pool>();

  auto& window_checker = *dependencies.window_checker;

  downlink_handler_impl handler(config, std::move(dependencies));

  resource_grid_reader_empty rg(1, 1, 1);
  resource_grid_context      rg_context;
  rg_context.slot   = slot_point(1, 1, 1);
  rg_context.sector = 1;

  // Set the OTA to the same slot as the grid.
  slot_symbol_point ota_time(rg_context.slot, 0, nof_symbols);

  // Delay the OTA, as the grid should always be advanced in slot.
  ota_time -= (nof_symbols + 1);

  window_checker.handle_new_ota_symbol(ota_time);

  handler.handle_dl_data(rg_context, rg);

  // Assert Control-Plane.
  ASSERT_TRUE(cplane_spy.has_enqueue_section_type_1_method_been_called());
  ASSERT_TRUE(uplane_spy.has_enqueue_section_type_1_method_been_called());
}
