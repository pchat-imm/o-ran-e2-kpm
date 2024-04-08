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

#ifndef E2AP_NODE_COMPONENT_CONFIG_ADD_WRAPPER_H
#define E2AP_NODE_COMPONENT_CONFIG_ADD_WRAPPER_H

#ifdef E2AP_V1

#elif E2AP_V2 
#include "v2_03/e2ap_types/common/e2ap_node_component_config_add.h"
#elif E2AP_V3 
#include "v3_01/e2ap_types/common/e2ap_node_component_config_add.h"
#else
static_assert(0!=0, "Unknown E2AP version");
#endif




#endif
