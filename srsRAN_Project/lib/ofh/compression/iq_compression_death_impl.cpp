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

#include "iq_compression_death_impl.h"
#include "srsran/support/error_handling.h"

using namespace srsran;
using namespace ofh;

void iq_compression_death_impl::compress(span<compressed_prb>         compressed_prbs,
                                         span<const cf_t>             iq_data,
                                         const ru_compression_params& params)
{
  report_error("Compression type {} is not supported", to_string(params.type));
}

void iq_compression_death_impl::decompress(span<cf_t>                   iq_data,
                                           span<const compressed_prb>   compressed_prbs,
                                           const ru_compression_params& params)
{
  report_error("Decompression type {} is not supported", to_string(params.type));
}
