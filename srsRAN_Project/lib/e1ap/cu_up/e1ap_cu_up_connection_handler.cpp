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

#include "e1ap_cu_up_connection_handler.h"

using namespace srsran;
using namespace srs_cu_up;

namespace {

/// Adapter used to convert E1AP Rx PDUs coming from the CU-CP into E1AP messages.
class e1ap_rx_pdu_adapter final : public e1ap_message_notifier
{
public:
  e1ap_rx_pdu_adapter(e1ap_message_handler& msg_handler_) : msg_handler(msg_handler_) {}

  void on_new_message(const e1ap_message& msg) override { msg_handler.handle_message(msg); }

private:
  e1ap_message_handler& msg_handler;
};

} // namespace

e1ap_cu_up_connection_handler::e1ap_cu_up_connection_handler(e1ap_connection_client& e1ap_client_handler_,
                                                             e1ap_message_handler&   e1ap_pdu_handler_) :
  e1ap_client_handler(e1ap_client_handler_),
  e1ap_pdu_handler(e1ap_pdu_handler_),
  logger(srslog::fetch_basic_logger("CU-UP-E1"))
{
}

SRSRAN_NODISCARD bool e1ap_cu_up_connection_handler::connect_to_cu_cp()
{
  e1ap_notifier =
      e1ap_client_handler.handle_cu_up_connection_request(std::make_unique<e1ap_rx_pdu_adapter>(e1ap_pdu_handler));

  return e1ap_notifier != nullptr;
}

void e1ap_cu_up_connection_handler::on_new_message(const e1ap_message& msg)
{
  if (is_connected()) {
    e1ap_notifier->on_new_message(msg);
  } else {
    logger.error("Discarding E1AP CU-UP message. Cause: Connection to CU-CP is dropped");
  }
}
