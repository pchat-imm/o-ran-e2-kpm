/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */


#ifndef E2_NODE_CONFIGURATION_UPDATE_ACK_ITEM_H
#define E2_NODE_CONFIGURATION_UPDATE_ACK_ITEM_H 

#include "e2ap_cause.h"
#include "e2ap_node_component_config_update.h"

typedef struct{
  e2_node_component_type_e e2_node_component_type;
  e2_node_component_id_present_e* id_present; // optional
  union {
    uint64_t gnb_cu_up_id;
    uint64_t gnb_du_id;
  };

 	long	 update_outcome; // delete
	cause_t *failure_cause;	/* OPTIONAL */
} e2_node_component_config_update_ack_item_t;

#endif


