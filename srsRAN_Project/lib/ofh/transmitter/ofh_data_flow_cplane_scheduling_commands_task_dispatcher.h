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

#include "ofh_data_flow_cplane_scheduling_commands.h"
#include "srsran/support/executors/task_executor.h"
#include <atomic>
#include <memory>

namespace srsran {
namespace ofh {

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow task dispatcher implementation entry.
struct data_flow_cplane_downlink_task_dispatcher_entry {
  data_flow_cplane_downlink_task_dispatcher_entry(
      std::unique_ptr<data_flow_cplane_scheduling_commands> data_flow_cplane_,
      task_executor&                                        executor_) :
    data_flow_cplane(std::move(data_flow_cplane_)), executor(executor_)
  {
    srsran_assert(data_flow_cplane, "Invalid data flow");
  }

  std::unique_ptr<data_flow_cplane_scheduling_commands> data_flow_cplane;
  task_executor&                                        executor;
};

/// Open Fronthaul Control-Plane scheduling and beamforming commands data flow task dispatcher implementation.
class data_flow_cplane_downlink_task_dispatcher : public data_flow_cplane_scheduling_commands
{
public:
  data_flow_cplane_downlink_task_dispatcher(std::vector<data_flow_cplane_downlink_task_dispatcher_entry>&& config_) :
    dispatchers(std::move(config_))
  {
  }

  // See interface for documentation.
  void enqueue_section_type_1_message(const data_flow_cplane_type_1_context& context) override
  {
    unsigned                                         index            = last_used++ % dispatchers.size();
    data_flow_cplane_downlink_task_dispatcher_entry& dispatcher       = dispatchers[index];
    data_flow_cplane_scheduling_commands&            data_flow_cplane = *dispatcher.data_flow_cplane;

    dispatcher.executor.execute(
        [&data_flow_cplane, context]() { data_flow_cplane.enqueue_section_type_1_message(context); });
  }

  // See interface for documentation.
  void enqueue_section_type_3_prach_message(const data_flow_cplane_scheduling_prach_context& context) override
  {
    unsigned                                         index            = last_used++ % dispatchers.size();
    data_flow_cplane_downlink_task_dispatcher_entry& dispatcher       = dispatchers[index];
    data_flow_cplane_scheduling_commands&            data_flow_cplane = *dispatcher.data_flow_cplane;

    dispatcher.executor.execute(
        [&data_flow_cplane, context]() { data_flow_cplane.enqueue_section_type_3_prach_message(context); });
  }

private:
  std::atomic<unsigned>                                        last_used = {0};
  std::vector<data_flow_cplane_downlink_task_dispatcher_entry> dispatchers;
};

} // namespace ofh
} // namespace srsran
