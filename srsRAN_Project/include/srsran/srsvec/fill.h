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

#include "srsran/srsvec/detail/traits.h"
#include "srsran/srsvec/types.h"

namespace srsran {
namespace srsvec {

/// \brief Sets all elements of a sequence to a given value.
///
/// \tparam T      Type of the sequence container, must be span-compatible.
/// \param  x      Sequence container.
/// \param  value  Value the sequence is set to. Must be compatible with the element type of the sequence.
template <typename T>
void fill(T&& x, detail::value_type_of_t<T> value)
{
  static_assert(detail::is_span_compatible<T>::value, "Template type is not compatible with a span");
  std::fill(x.begin(), x.end(), value);
}

} // namespace srsvec
} // namespace srsran
