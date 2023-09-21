/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
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

#include "ogs-app.h"

static ogs_app_context_t self;

static int initialized = 0;

static void app_context_prepare(void);

int ogs_app_context_init(void)
{
    ogs_assert(initialized == 0);

    memset(&self, 0, sizeof(ogs_app_context_t));

    app_context_prepare();

    initialized = 1;

    return OGS_OK;
}

void ogs_app_context_final(void)
{
    ogs_assert(initialized == 1);

    if (self.document) {
        yaml_document_delete(self.document);
        free(self.document);
    }

    if (self.pollset)
        ogs_pollset_destroy(self.pollset);
    if (self.timer_mgr)
        ogs_timer_mgr_destroy(self.timer_mgr);
    if (self.queue)
        ogs_queue_destroy(self.queue);

    initialized = 0;
}

ogs_app_context_t *ogs_app(void)
{
    return &self;
}

static void recalculate_pool_size(void)
{
    self.pool.packet = self.max.ue * OGS_MAX_NUM_OF_PACKET_BUFFER;

#define MAX_NUM_OF_TUNNEL       3   /* Num of Tunnel per Bearer */
    self.pool.sess = self.max.ue * OGS_MAX_NUM_OF_SESS;
    self.pool.bearer = self.pool.sess * OGS_MAX_NUM_OF_BEARER;
    self.pool.tunnel = self.pool.bearer * MAX_NUM_OF_TUNNEL;

#define POOL_NUM_PER_UE 16
    self.pool.timer = self.max.ue * POOL_NUM_PER_UE;
    self.pool.message = self.max.ue * POOL_NUM_PER_UE;
    self.pool.event = self.max.ue * POOL_NUM_PER_UE;
    self.pool.socket = self.max.ue * POOL_NUM_PER_UE;
    self.pool.xact = self.max.ue * POOL_NUM_PER_UE;
    self.pool.stream = self.max.ue * POOL_NUM_PER_UE;

    self.pool.nf = self.max.peer;
#define NF_SERVICE_PER_NF_INSTANCE 16
    self.pool.nf_service = self.pool.nf * NF_SERVICE_PER_NF_INSTANCE;
    self.pool.subscription = self.pool.nf * NF_SERVICE_PER_NF_INSTANCE;

    self.pool.gtp_node = self.pool.nf;
    if (self.max.gtp_peer)
        self.pool.gtp_node = self.max.gtp_peer;

    /* Num of TAI-LAI Mapping Table */
    self.pool.csmap = self.pool.nf;

#define MAX_NUM_OF_IMPU         8
    self.pool.impi = self.max.ue;
    self.pool.impu = self.pool.impi * MAX_NUM_OF_IMPU;
}

static void regenerate_all_timer_duration(void)
{
    ogs_assert(self.time.message.duration);

    self.time.message.sbi.client_wait_duration = self.time.message.duration;
    self.time.message.sbi.connection_deadline =
        self.time.message.sbi.client_wait_duration + ogs_time_from_sec(1);
    self.time.message.sbi.nf_register_interval =
        ogs_max(ogs_time_from_sec(3),
            self.time.message.sbi.client_wait_duration + ogs_time_from_sec(1));
    self.time.message.sbi.nf_register_interval_in_exception =
                ogs_time_from_sec(2);

#define PFCP_N1_RESPONSE_RETRY_COUNT  3
    self.time.message.pfcp.n1_response_rcount = PFCP_N1_RESPONSE_RETRY_COUNT;
    self.time.message.pfcp.t1_response_duration =
        (self.time.message.duration /
         (self.time.message.pfcp.n1_response_rcount + 1));
    ogs_assert(self.time.message.pfcp.t1_response_duration);

#define PFCP_N1_HOLDING_RETRY_COUNT 1
    self.time.message.pfcp.n1_holding_rcount = PFCP_N1_HOLDING_RETRY_COUNT;
    self.time.message.pfcp.t1_holding_duration =
        self.time.message.pfcp.n1_response_rcount *
        self.time.message.pfcp.t1_response_duration;
    ogs_assert(self.time.message.pfcp.t1_holding_duration);

    self.time.message.pfcp.association_interval =
        ogs_max(ogs_time_from_sec(3),
            self.time.message.sbi.client_wait_duration + ogs_time_from_sec(1));

    self.time.message.pfcp.no_heartbeat_duration =
        ogs_max(ogs_time_from_sec(10),
            self.time.message.sbi.client_wait_duration + ogs_time_from_sec(1));

#define GTP_N3_RESPONSE_RETRY_COUNT  3
    self.time.message.gtp.n3_response_rcount = GTP_N3_RESPONSE_RETRY_COUNT;
    self.time.message.gtp.t3_response_duration =
        (self.time.message.duration /
         (self.time.message.gtp.n3_response_rcount + 1));
    ogs_assert(self.time.message.gtp.t3_response_duration);

#define GTP_N3_HOLDING_RETRY_COUNT 1
    self.time.message.gtp.n3_holding_rcount = GTP_N3_HOLDING_RETRY_COUNT;
    self.time.message.gtp.t3_holding_duration =
        self.time.message.gtp.n3_response_rcount *
        self.time.message.gtp.t3_response_duration;
    ogs_assert(self.time.message.gtp.t3_holding_duration);

#if 0
    ogs_trace("%lld, %lld, %lld, %d, %lld, %d %lld, %d, %lld, %d, %lld",
        (long long)self.time.message.duration,
        (long long)self.time.message.sbi.client_wait_duration,
        (long long)self.time.message.sbi.connection_deadline,
        self.time.message.pfcp.n1_response_rcount,
        (long long)self.time.message.pfcp.t1_response_duration,
        self.time.message.pfcp.n1_holding_rcount,
        (long long)self.time.message.pfcp.t1_holding_duration,
        self.time.message.gtp.n3_response_rcount,
        (long long)self.time.message.gtp.t3_response_duration,
        self.time.message.gtp.n3_holding_rcount,
        (long long)self.time.message.gtp.t3_holding_duration);
    ogs_trace("%lld, %lld, %lld",
        (long long)self.time.message.sbi.nf_register_interval,
        (long long)self.time.message.pfcp.association_interval,
        (long long)self.time.message.pfcp.no_heartbeat_duration);
#endif
}

static void app_context_prepare(void)
{
#define USRSCTP_LOCAL_UDP_PORT      9899
    self.usrsctp.udp_port = USRSCTP_LOCAL_UDP_PORT;

    self.sockopt.no_delay = true;

#define MAX_NUM_OF_UE               1024    /* Num of UEs */
#define MAX_NUM_OF_PEER             64      /* Num of Peer */

    self.max.ue = MAX_NUM_OF_UE;
    self.max.peer = MAX_NUM_OF_PEER;

    ogs_pkbuf_default_init(&self.pool.defconfig);

    recalculate_pool_size();

    /* <Heartbeat Checking Interval>
     *  Heartbeat Interval(e.g: 10 seconds) + No Heartbeat Margin(1 second) */
    self.time.nf_instance.no_heartbeat_margin = 1;

    /* 3600 seconds = 1 hour */
    self.time.nf_instance.validity_duration = 3600;

    /* 86400 seconds = 1 day */
    self.time.subscription.validity_duration = 86400;

    /*
     * Message Wait Duration : 10 seconds (Default)
     *
     * The paging retry timer is 2 seconds and the retry count is 3.
     *
     * It is recomended to set at least 9 seconds to reflect
     * the paging failure result to GTPv2-C or HTTP2(SBI).
     */
    self.time.message.duration = ogs_time_from_sec(10);

    /*
     * Handover Wait Duration : 300 ms (Default)
     *
     * Time to wait for AMF/MME to send UEContextReleaseCommand
     * to the source gNB/eNB after receiving HandoverNotify
     */
    self.time.handover.duration = ogs_time_from_msec(300);

    /* Size of internal metrics pool (amount of ogs_metrics_spec_t) */
    self.metrics.max_specs = 512;

    regenerate_all_timer_duration();
}

static int app_context_validation(void)
{
    if (self.parameter.no_ipv4 == 1 &&
        self.parameter.no_ipv6 == 1) {
        ogs_error("Both `no_ipv4` and `no_ipv6` set to `true` in `%s`",
                self.file);
        return OGS_ERROR;
    }

    if (self.time.nf_instance.validity_duration == 0) {
        ogs_error("NF Instance validity-time should not 0");
        ogs_error("time:");
        ogs_error("  nf_instance:");
        ogs_error("    validity: 0");

        return OGS_ERROR;
    }

    return OGS_OK;
}

int ogs_app_context_parse_config(void)
{
    int rv;
    yaml_document_t *document = NULL;
    ogs_yaml_iter_t root_iter;

    document = self.document;
    ogs_assert(document);

    ogs_yaml_iter_init(&root_iter, document);
    while (ogs_yaml_iter_next(&root_iter)) {
        const char *root_key = ogs_yaml_iter_key(&root_iter);
        ogs_assert(root_key);
        if (!strcmp(root_key, "db_uri")) {
            self.db_uri = ogs_yaml_iter_value(&root_iter);
        } else if (!strcmp(root_key, "logger")) {
            ogs_yaml_iter_t logger_iter;
            ogs_yaml_iter_recurse(&root_iter, &logger_iter);
            while (ogs_yaml_iter_next(&logger_iter)) {
                const char *logger_key = ogs_yaml_iter_key(&logger_iter);
                ogs_assert(logger_key);
                if (!strcmp(logger_key, "file")) {
                    self.logger.file = ogs_yaml_iter_value(&logger_iter);
                } else if (!strcmp(logger_key, "level")) {
                    self.logger.level =
                        ogs_yaml_iter_value(&logger_iter);
                } else if (!strcmp(logger_key, "domain")) {
                    self.logger.domain =
                        ogs_yaml_iter_value(&logger_iter);
                }
            }
        } else if (!strcmp(root_key, "parameter")) {
            ogs_yaml_iter_t parameter_iter;
            ogs_yaml_iter_recurse(&root_iter, &parameter_iter);
            while (ogs_yaml_iter_next(&parameter_iter)) {
                const char *parameter_key = ogs_yaml_iter_key(&parameter_iter);
                ogs_assert(parameter_key);
                if (!strcmp(parameter_key, "no_hss")) {
                    self.parameter.no_hss =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_mme")) {
                    self.parameter.no_mme =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_sgwu")) {
                    self.parameter.no_sgwu =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_sgwc")) {
                    self.parameter.no_sgwc =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_sgw")) {
                    self.parameter.no_sgw =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_pgw")) {
                    self.parameter.no_pgw =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_pcrf")) {
                    self.parameter.no_pcrf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_nrf")) {
                    self.parameter.no_nrf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_scp")) {
                    self.parameter.no_scp =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_amf")) {
                    self.parameter.no_amf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_smf")) {
                    self.parameter.no_smf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_upf")) {
                    self.parameter.no_upf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_ausf")) {
                    self.parameter.no_ausf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_udm")) {
                    self.parameter.no_udm =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_pcf")) {
                    self.parameter.no_pcf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_nssf")) {
                    self.parameter.no_nssf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_bsf")) {
                    self.parameter.no_bsf =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_udr")) {
                    self.parameter.no_udr =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_ipv4")) {
                    self.parameter.no_ipv4 =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_ipv6")) {
                    self.parameter.no_ipv6 =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "prefer_ipv4")) {
                    self.parameter.prefer_ipv4 =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "multicast")) {
                    self.parameter.multicast =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "use_openair")) {
                    self.parameter.use_openair =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(
                    parameter_key, "no_ipv4v6_local_addr_in_packet_filter")) {
                    self.parameter.no_ipv4v6_local_addr_in_packet_filter =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key, "no_pfcp_rr_select")) {
                    self.parameter.no_pfcp_rr_select =
                        ogs_yaml_iter_bool(&parameter_iter);
                } else if (!strcmp(parameter_key,
                            "use_mongodb_change_stream")) {
                    self.use_mongodb_change_stream = 
                        ogs_yaml_iter_bool(&parameter_iter);
                } else
                    ogs_warn("unknown key `%s`", parameter_key);
            }
        } else if (!strcmp(root_key, "sockopt")) {
            ogs_yaml_iter_t sockopt_iter;
            ogs_yaml_iter_recurse(&root_iter, &sockopt_iter);
            while (ogs_yaml_iter_next(&sockopt_iter)) {
                const char *sockopt_key = ogs_yaml_iter_key(&sockopt_iter);
                ogs_assert(sockopt_key);
                if (!strcmp(sockopt_key, "no_delay")) {
                    self.sockopt.no_delay =
                        ogs_yaml_iter_bool(&sockopt_iter);
                } else if (!strcmp(sockopt_key, "linger")) {
                    const char *v = ogs_yaml_iter_value(&sockopt_iter);
                    if (v) self.sockopt.l_linger = atoi(v);
                    self.sockopt.l_onoff = true;
                } else
                    ogs_warn("unknown key `%s`", sockopt_key);
            }
        } else if (!strcmp(root_key, "max")) {
            ogs_yaml_iter_t max_iter;
            ogs_yaml_iter_recurse(&root_iter, &max_iter);
            while (ogs_yaml_iter_next(&max_iter)) {
                const char *max_key = ogs_yaml_iter_key(&max_iter);
                ogs_assert(max_key);
                if (!strcmp(max_key, "ue")) {
                    const char *v = ogs_yaml_iter_value(&max_iter);
                    if (v) self.max.ue = atoi(v);
                } else if (!strcmp(max_key, "peer") ||
                            !strcmp(max_key, "enb")) {
                    const char *v = ogs_yaml_iter_value(&max_iter);
                    if (v) self.max.peer = atoi(v);
                } else if (!strcmp(max_key, "gtp_peer") ||
                            !strcmp(max_key, "enb")) {
                    const char *v = ogs_yaml_iter_value(&max_iter);
                    if (v) self.max.gtp_peer = atoi(v);
                } else
                    ogs_warn("unknown key `%s`", max_key);
            }

            recalculate_pool_size();
        } else if (!strcmp(root_key, "pool")) {
            ogs_yaml_iter_t pool_iter;
            ogs_yaml_iter_recurse(&root_iter, &pool_iter);
            while (ogs_yaml_iter_next(&pool_iter)) {
                const char *pool_key = ogs_yaml_iter_key(&pool_iter);
                ogs_assert(pool_key);
                if (!strcmp(pool_key, "128")) {
                    const char *v = ogs_yaml_iter_value(&pool_iter);
                    if (v)
                        self.pool.defconfig.cluster_128_pool = atoi(v);
                } else if (!strcmp(pool_key, "256")) {
                    const char *v = ogs_yaml_iter_value(&pool_iter);
                    if (v)
                        self.pool.defconfig.cluster_256_pool = atoi(v);
                } else if (!strcmp(pool_key, "512")) {
                    const char *v = ogs_yaml_iter_value(&pool_iter);
                    if (v)
                        self.pool.defconfig.cluster_512_pool = atoi(v);
                } else if (!strcmp(pool_key, "1024")) {
                    const char *v = ogs_yaml_iter_value(&pool_iter);
                    if (v)
                        self.pool.defconfig.cluster_1024_pool = atoi(v);
                } else if (!strcmp(pool_key, "2048")) {
                    const char *v = ogs_yaml_iter_value(&pool_iter);
                    if (v)
                        self.pool.defconfig.cluster_2048_pool = atoi(v);
                } else if (!strcmp(pool_key, "8192")) {
                    const char *v = ogs_yaml_iter_value(&pool_iter);
                    if (v)
                        self.pool.defconfig.cluster_8192_pool = atoi(v);
                } else if (!strcmp(pool_key, "32768")) {
                    const char *v = ogs_yaml_iter_value(&pool_iter);
                    if (v)
                        self.pool.defconfig.cluster_32768_pool = atoi(v);
                } else if (!strcmp(pool_key, "big")) {
                    const char *v = ogs_yaml_iter_value(&pool_iter);
                    if (v)
                        self.pool.defconfig.cluster_big_pool = atoi(v);
                } else
                    ogs_warn("unknown key `%s`", pool_key);
            }
        } else if (!strcmp(root_key, "time")) {
            ogs_yaml_iter_t time_iter;
            ogs_yaml_iter_recurse(&root_iter, &time_iter);
            while (ogs_yaml_iter_next(&time_iter)) {
                const char *time_key = ogs_yaml_iter_key(&time_iter);
                ogs_assert(time_key);
                if (!strcmp(time_key, "nf_instance")) {
                    ogs_yaml_iter_t sbi_iter;
                    ogs_yaml_iter_recurse(&time_iter, &sbi_iter);

                    while (ogs_yaml_iter_next(&sbi_iter)) {
                        const char *sbi_key =
                            ogs_yaml_iter_key(&sbi_iter);
                        ogs_assert(sbi_key);

                        if (!strcmp(sbi_key, "heartbeat")) {
                            const char *v = ogs_yaml_iter_value(&sbi_iter);
                            if (v) self.time.nf_instance.heartbeat_interval =
                                        atoi(v);
                        } else if (!strcmp(sbi_key, "validity")) {
                            const char *v = ogs_yaml_iter_value(&sbi_iter);
                            if (v) self.time.nf_instance.validity_duration =
                                        atoi(v);
                        } else
                            ogs_warn("unknown key `%s`", sbi_key);
                    }
                } else if (!strcmp(time_key, "subscription")) {
                    ogs_yaml_iter_t sbi_iter;
                    ogs_yaml_iter_recurse(&time_iter, &sbi_iter);

                    while (ogs_yaml_iter_next(&sbi_iter)) {
                        const char *sbi_key =
                            ogs_yaml_iter_key(&sbi_iter);
                        ogs_assert(sbi_key);

                        if (!strcmp(sbi_key, "validity")) {
                            const char *v = ogs_yaml_iter_value(&sbi_iter);
                            if (v) self.time.subscription.validity_duration =
                                        atoi(v);
                        } else
                            ogs_warn("unknown key `%s`", sbi_key);
                    }
                } else if (!strcmp(time_key, "message")) {
                    ogs_yaml_iter_t msg_iter;
                    ogs_yaml_iter_recurse(&time_iter, &msg_iter);

                    while (ogs_yaml_iter_next(&msg_iter)) {
                        const char *msg_key =
                            ogs_yaml_iter_key(&msg_iter);
                        ogs_assert(msg_key);

                        if (!strcmp(msg_key, "duration")) {
                            const char *v = ogs_yaml_iter_value(&msg_iter);
                            if (v) {
                                self.time.message.duration =
                                    ogs_time_from_msec(atoll(v));
                                regenerate_all_timer_duration();
                            }
                        } else
                            ogs_warn("unknown key `%s`", msg_key);
                    }
                } else if (!strcmp(time_key, "handover")) {
                    ogs_yaml_iter_t msg_iter;
                    ogs_yaml_iter_recurse(&time_iter, &msg_iter);

                    while (ogs_yaml_iter_next(&msg_iter)) {
                        const char *msg_key =
                            ogs_yaml_iter_key(&msg_iter);
                        ogs_assert(msg_key);

                        if (!strcmp(msg_key, "duration")) {
                            const char *v = ogs_yaml_iter_value(&msg_iter);
                            if (v) {
                                self.time.handover.duration =
                                    ogs_time_from_msec(atoll(v));
                            }
                        } else
                            ogs_warn("unknown key `%s`", msg_key);
                    }
                } else if (!strcmp(time_key, "t3502")) {
                    /* handle config in amf */
                } else if (!strcmp(time_key, "t3512")) {
                    /* handle config in amf */
                } else if (!strcmp(time_key, "t3402")) {
                    /* handle config in mme */
                } else if (!strcmp(time_key, "t3412")) {
                    /* handle config in mme */
                } else if (!strcmp(time_key, "t3423")) {
                    /* handle config in mme */
                } else
                    ogs_warn("unknown key `%s`", time_key);
            }
        } else if (!strcmp(root_key, "sbi")) {
            ogs_yaml_iter_t tls_iter;
            ogs_yaml_iter_recurse(&root_iter, &tls_iter);
            while (ogs_yaml_iter_next(&tls_iter)) {
                const char *tls_key = ogs_yaml_iter_key(&tls_iter);
                ogs_assert(tls_key);
                if (!strcmp(tls_key, "server")) {
                    ogs_yaml_iter_t server_iter;
                    ogs_yaml_iter_recurse(&tls_iter, &server_iter);

                    while (ogs_yaml_iter_next(&server_iter)) {
                        const char *server_key =
                            ogs_yaml_iter_key(&server_iter);
                        ogs_assert(server_key);
                        if (!strcmp(server_key, "no_tls")) {
                            self.sbi.server.no_tls =
                                ogs_yaml_iter_bool(&server_iter);
                        } else if (!strcmp(server_key, "no_verify")) {
                            self.sbi.server.no_verify =
                                ogs_yaml_iter_bool(&server_iter);
                        } else if (!strcmp(server_key, "cacert")) {
                            self.sbi.server.cacert =
                                ogs_yaml_iter_value(&server_iter);
                        } else if (!strcmp(server_key, "cert")) {
                            self.sbi.server.cert =
                                ogs_yaml_iter_value(&server_iter);
                        } else if (!strcmp(server_key, "key")) {
                            self.sbi.server.key =
                                ogs_yaml_iter_value(&server_iter);
                        } else
                            ogs_warn("unknown key `%s`", server_key);
                    }
                } else if (!strcmp(tls_key, "client")) {
                    ogs_yaml_iter_t client_iter;
                    ogs_yaml_iter_recurse(&tls_iter, &client_iter);

                    while (ogs_yaml_iter_next(&client_iter)) {
                        const char *client_key =
                            ogs_yaml_iter_key(&client_iter);
                        ogs_assert(client_key);
                        if (!strcmp(client_key, "no_tls")) {
                            self.sbi.client.no_tls =
                                ogs_yaml_iter_bool(&client_iter);
                        } else if (!strcmp(client_key, "no_verify")) {
                            self.sbi.client.no_verify =
                                ogs_yaml_iter_bool(&client_iter);
                        } else if (!strcmp(client_key, "cacert")) {
                            self.sbi.client.cacert =
                                ogs_yaml_iter_value(&client_iter);
                        } else if (!strcmp(client_key, "cert")) {
                            self.sbi.client.cert =
                                ogs_yaml_iter_value(&client_iter);
                        } else if (!strcmp(client_key, "key")) {
                            self.sbi.client.key =
                                ogs_yaml_iter_value(&client_iter);
                        } else
                            ogs_warn("unknown key `%s`", client_key);
                    }
                } else
                    ogs_warn("unknown key `%s`", tls_key);
            }
        }
    }

    rv = app_context_validation();
    if (rv != OGS_OK) return rv;

    return OGS_OK;
}
