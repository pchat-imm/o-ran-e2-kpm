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

#include "srsran/adt/span.h"
#include "srsran/ofh/ofh_ota_symbol_handler.h"
#include "srsran/support/executors/task_executor.h"

namespace srsran {
namespace ofh {

/// OTA symbol task dispatcher for the transmitter.
class transmitter_ota_symbol_task_dispatcher : public ota_symbol_handler
{
public:
  transmitter_ota_symbol_task_dispatcher(task_executor&      executor_,
                                         ota_symbol_handler& window_checker_,
                                         ota_symbol_handler& symbol_handler_) :
    executor(executor_), window_checker(window_checker_), symbol_handler(symbol_handler_)
  {
  }

  void handle_new_ota_symbol(slot_symbol_point symbol_point) override
  {
    window_checker.handle_new_ota_symbol(symbol_point);

    executor.execute([&, symbol_point]() { symbol_handler.handle_new_ota_symbol(symbol_point); });
  }

private:
  task_executor&      executor;
  ota_symbol_handler& window_checker;
  ota_symbol_handler& symbol_handler;
};

} // namespace ofh
} // namespace srsran
