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

#include "ru_downlink_handler_generic_impl.h"
#include "srsran/phy/lower/lower_phy_rg_handler.h"

using namespace srsran;

void ru_downlink_handler_generic_impl::handle_dl_data(const resource_grid_context& context,
                                                      const resource_grid_reader&  grid)
{
  srsran_assert(context.sector < handler.size(), "Invalid sector {}", context.sector);

  handler[context.sector]->handle_resource_grid(context, grid);
}
