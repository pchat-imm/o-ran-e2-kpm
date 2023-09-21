/*
 * Copyright (C) 2019-2022 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SCP_CONTEXT_H
#define SCP_CONTEXT_H

#include "ogs-sbi.h"
#include "ogs-app.h"

#include "scp-sm.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int __scp_log_domain;

#undef OGS_LOG_DOMAIN
#define OGS_LOG_DOMAIN __scp_log_domain

typedef struct scp_context_s {
    ogs_list_t          assoc_list;
} scp_context_t;

typedef struct scp_assoc_s scp_assoc_t;

typedef struct scp_assoc_s {
    ogs_sbi_object_t sbi;

    ogs_sbi_stream_t *stream;

    ogs_sbi_client_t *client;
    ogs_sbi_client_t *nrf_client;

    ogs_sbi_request_t *request;
    ogs_sbi_service_type_e service_type;
    OpenAPI_nf_type_e requester_nf_type;

    ogs_sbi_nf_instance_t *nf_service_producer;
} scp_assoc_t;

void scp_context_init(void);
void scp_context_final(void);
scp_context_t *scp_self(void);

int scp_context_parse_config(void);

scp_assoc_t *scp_assoc_add(ogs_sbi_stream_t *stream);
void scp_assoc_remove(scp_assoc_t *sess);
void scp_assoc_remove_all(void);

scp_assoc_t *scp_assoc_find(uint32_t index);

#ifdef __cplusplus
}
#endif

#endif /* SCP_CONTEXT_H */
