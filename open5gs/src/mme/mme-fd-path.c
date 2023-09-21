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

#include "mme-event.h"
#include "mme-fd-path.h"

/* handler for Cancel-Location-Request cb */
static struct disp_hdl *hdl_s6a_clr = NULL;

/* handler for Insert-Subscriber-Data-Request cb */
static struct disp_hdl *hdl_s6a_idr = NULL;

static struct session_handler *mme_s6a_reg = NULL;

/* s6a process Subscription-Data from avp */
static int mme_s6a_subscription_data_from_avp(struct avp *avp,
    ogs_subscription_data_t *subscription_data,
    mme_ue_t *mme_ue, uint32_t *subdatamask);

struct sess_state {
    mme_ue_t *mme_ue;
    struct timespec ts; /* Time of sending the message */
};

static void mme_s6a_aia_cb(void *data, struct msg **msg);
static void mme_s6a_ula_cb(void *data, struct msg **msg);
static void mme_s6a_pua_cb(void *data, struct msg **msg);

static void state_cleanup(struct sess_state *sess_data, os0_t sid, void *opaque)
{
    ogs_free(sess_data);
}

/* s6a process Subscription-Data from avp */
static int mme_s6a_subscription_data_from_avp(struct avp *avp,
    ogs_subscription_data_t *subscription_data,
    mme_ue_t *mme_ue, uint32_t *subdatamask)
{
    int ret;
    int error = 0;
    char buf[OGS_CHRGCHARS_LEN];
    struct avp *avpch1, *avpch2, *avpch3, *avpch4, *avpch5;
    struct avp_hdr *hdr;
    ogs_sockaddr_t addr;

    ogs_assert(avp);
    ogs_assert(subscription_data);
    ogs_assert(mme_ue);
    ogs_assert(subdatamask);

    /* AVP: 'MSISDN'( 701 )
     * The MSISDN AVP is of type OctetString. This AVP contains an MSISDN,
     * in international number format as described in ITU-T Rec E.164 [8],
     * encoded as a TBCD-string, i.e. digits from 0 through 9 are encoded
     * 0000 to 1001; 1111 is used as a filler when there is an odd number
     * of digits; bits 8 to 5 of octet n encode digit 2n; bits 4 to 1 of
     * octet n encode digit 2(n-1)+1.
     * Reference: 3GPP TS 29.329
     */
    ret = fd_avp_search_avp(avp, ogs_diam_s6a_msisdn, &avpch1);
    ogs_assert(ret == 0);
    if (avpch1) {
        ret = fd_msg_avp_hdr(avpch1, &hdr);
        ogs_assert(ret == 0);
        if (hdr->avp_value->os.data && hdr->avp_value->os.len) {
            mme_ue->msisdn_len = hdr->avp_value->os.len;
            memcpy(mme_ue->msisdn, hdr->avp_value->os.data,
                    ogs_min(mme_ue->msisdn_len, OGS_MAX_MSISDN_LEN));
            ogs_buffer_to_bcd(mme_ue->msisdn,
                    mme_ue->msisdn_len, mme_ue->msisdn_bcd);
            *subdatamask = (*subdatamask | OGS_DIAM_S6A_SUBDATA_MSISDN);
        }
    }

    /* AVP: 'A-MSISDN'(1643)
     * The A-MSISDN AVP contains an A-MSISDN, in international number
     * format as described in ITU-T Rec E.164, encoded as a TBCD-string.
     * This AVP shall not include leading indicators for the nature of
     * address and the numbering plan; it shall contain only the
     * TBCD-encoded digits of the address.
     * Reference: 3GPP TS 29.272 7.3.157
     */
    ret = fd_avp_search_avp(avp, ogs_diam_s6a_a_msisdn, &avpch1);
    ogs_assert(ret == 0);
    if (avpch1) {
        ret = fd_msg_avp_hdr(avpch1, &hdr);
        ogs_assert(ret == 0);
        if (hdr->avp_value->os.data && hdr->avp_value->os.len) {
            mme_ue->a_msisdn_len = hdr->avp_value->os.len;
            memcpy(mme_ue->a_msisdn, hdr->avp_value->os.data,
                    ogs_min(mme_ue->a_msisdn_len, OGS_MAX_MSISDN_LEN));
            ogs_buffer_to_bcd(mme_ue->a_msisdn,
                    mme_ue->a_msisdn_len, mme_ue->a_msisdn_bcd);
            *subdatamask = (*subdatamask | OGS_DIAM_S6A_SUBDATA_A_MSISDN);
        }
    }

    /* AVP: 'Network-Access-Mode'(1417)
     * The Network-Access-Mode AVP shall indicate one of three options
     * through its value.
     * (EPS-IMSI-COMBINED/RESERVED/EPS-ONLY)
     * Reference: 3GPP TS 29.272 7.3.21
     */
    ret = fd_avp_search_avp(avp, ogs_diam_s6a_network_access_mode, &avpch1);
    ogs_assert(ret == 0);
    if (avpch1) {
        ret = fd_msg_avp_hdr(avpch1, &hdr);
        ogs_assert(ret == 0);
        mme_ue->network_access_mode = hdr->avp_value->i32;
        *subdatamask = (*subdatamask | OGS_DIAM_S6A_SUBDATA_NAM);
    }

    /* AVP: '3GPP-Charging-Characteristics'(13)
     * For GGSN, it contains the charging characteristics for 
     * this PDP Context received in the Create PDP Context 
     * Request Message (only available in R99 and later releases). 
     * For PGW, it contains the charging characteristics for the 
     * IP-CAN bearer.
     * Reference: 3GPP TS 29.061 16.4.7.2 13
     */
    ret = fd_avp_search_avp(avp, ogs_diam_s6a_3gpp_charging_characteristics, 
        &avpch1);
    ogs_assert(ret == 0);
    if (avpch1) {
        ret = fd_msg_avp_hdr(avpch1, &hdr);
        ogs_ascii_to_hex(
            (char*)hdr->avp_value->os.data, (int)hdr->avp_value->os.len,
            buf, sizeof(buf));
        memcpy(mme_ue->charging_characteristics, buf, OGS_CHRGCHARS_LEN);
        mme_ue->charging_characteristics_presence = true;
        *subdatamask = (*subdatamask | OGS_DIAM_S6A_SUBDATA_CC);
    }

    /* AVP: 'AMBR'(1435)
     * The Amber AVP contains the Max-Requested-Bandwidth-UL and
     * Max-Requested-Bandwidth-DL AVPs.
     * Reference: 3GPP TS 29.272 7.3.41
     */
    ret = fd_avp_search_avp(avp, ogs_diam_s6a_ambr, &avpch1);
    ogs_assert(ret == 0);
    if (avpch1) {
        /* AVP: 'Max-Requested-Bandwidth-UL'(516)
         * The Max -Bandwidth-UL AVP indicates the maximum requested
         * bandwidth in bits per second for an uplink IP flow.
         * Reference: 3GPP TS 29.212 7.3.41
         */
        ret = fd_avp_search_avp(avpch1,
                ogs_diam_s6a_max_bandwidth_ul, &avpch2);
        ogs_assert(ret == 0);
        if (avpch2) {
            ret = fd_msg_avp_hdr(avpch2, &hdr);
            ogs_assert(ret == 0);
            subscription_data->ambr.uplink = hdr->avp_value->u32;
        } else {
            ogs_error("no_Max-Bandwidth-UL");
            error++;
        }

        /* AVP: 'Max-Requested-Bandwidth-DL'(515)
         * The Max-Requested-Bandwidth-DL AVP indicates the maximum
         * bandwidth in bits per second for a downlink IP flow.
         * Reference: 3GPP TS 29.212 7.3.41
         */
        ret = fd_avp_search_avp(avpch1,
                ogs_diam_s6a_max_bandwidth_dl, &avpch2);
        ogs_assert(ret == 0);
        if (avpch2) {
            ret = fd_msg_avp_hdr(avpch2, &hdr);
            ogs_assert(ret == 0);
            subscription_data->ambr.downlink = hdr->avp_value->u32;
        } else {
            ogs_error("no_Max-Bandwidth-DL");
            error++;
        }
        *subdatamask = (*subdatamask | OGS_DIAM_S6A_SUBDATA_UEAMBR);
    }

    /* AVP: 'Subscribed-Periodic-RAU-TAU-Timer'(1619)
     * The Subscribed-Periodic-TAU-RAU-Timer AVP contains the subscribed
     * periodic TAU/RAU timer value in seconds.
     * Reference: 3GPP TS 29.272 7.3.134
     */
    ret = fd_avp_search_avp(avp,
            ogs_diam_s6a_subscribed_rau_tau_timer, &avpch1);
    ogs_assert(ret == 0);
    if (avpch1) {
        ret = fd_msg_avp_hdr(avpch1, &hdr);
        ogs_assert(ret == 0);
        subscription_data->subscribed_rau_tau_timer = hdr->avp_value->i32;
        *subdatamask = (*subdatamask | OGS_DIAM_S6A_SUBDATA_RAU_TAU_TIMER);
    }

    /* AVP: 'APN-Configuration-Profile'(1429)
     * The APN-Configuration-Profile AVP shall contain the information
     * related to the user's subscribed APN configurations for EPS. The
     * Context-Identifier AVP within it shall identify the per subscriber's
     * default APN configuration. The Subscription-Data AVP associated
     * with an IMSI contains one APN-Configuration-Profile AVP. Each
     * APN-Configuration-Profile AVP contains one or more APN-Configuration
     * AVPs. Each APN-Configuration AVP describes the configuration for a
     * single APN. Therefore, the cardinality of the relationship between
     * IMSI and APN is one-to-many.
     * Reference: 3GPP TS 29.272 7.3.34
     */
    ret = fd_avp_search_avp(avp,
            ogs_diam_s6a_apn_configuration_profile, &avpch1);
    ogs_assert(ret == 0);
    if (avpch1) {
        ogs_slice_data_t *slice_data = NULL;

        ret = fd_msg_browse(avpch1, MSG_BRW_FIRST_CHILD, &avpch2, NULL);
        ogs_assert(ret == 0);

        ogs_assert(subscription_data->num_of_slice == 0);
        slice_data = &subscription_data->slice[0];
        while (avpch2) {
            ret = fd_msg_avp_hdr(avpch2, &hdr);
            ogs_assert(ret == 0);
            switch(hdr->avp_code) {

            /* AVP: 'Context-Identifier'(1423)
             * The Context-Identifier in the APN-Configuration AVP shall
             * identify that APN configuration, and it shall not have a
             * value of zero. Furthermore, the Context-Identifier in the
             * APN-Configuration AVP shall uniquely identify the EPS APN
             * configuration per subscription.
             * Reference: 3GPP TS 29.272 7.3.35
             */
            case OGS_DIAM_S6A_AVP_CODE_CONTEXT_IDENTIFIER:
                slice_data->context_identifier = hdr->avp_value->i32;
                break;

            /* AVP: 'All-APN-Configurations-Included-Indicator'(1428)
             * Reference: 3GPP TS 29.272 7.3.33
             */
            case OGS_DIAM_S6A_AVP_CODE_ALL_APN_CONFIG_INC_IND:
                slice_data->all_apn_config_inc = hdr->avp_value->i32;
                break;

            /* AVP: 'APN-Configuration'(1430)
             * The APN-Configuration AVP contains the information
             * related to the user's subscribed APN configurations.
             * Reference: 3GPP TS 29.272 7.3.35
             */
            case OGS_DIAM_S6A_AVP_CODE_APN_CONFIGURATION:
            {
                ogs_session_t *session = NULL;

                if (slice_data->num_of_session >= OGS_MAX_NUM_OF_SESS) {
                    ogs_warn("Ignore max session count overflow [%d>=%d]",
                        slice_data->num_of_session, OGS_MAX_NUM_OF_SESS);
                    break;
                }
                session = &slice_data->session[slice_data->num_of_session];
                ogs_assert(session);

                /* AVP: 'Service-Selection'(493)
                 * The Service-Selection AVP is of type of UTF8String. This
                 * AVP shall contain either the APN Network Identifier
                 * (i.e. an APN without the Operator Identifier) per 3GPP
                 * TS 23.003 [3], clauses 9.1 & 9.1.1, or this AVP shall
                 * contain the wild card value per 3GPP TS 23.003 [3],
                 * clause 9.2.1, and 3GPP TS 23.008 [30], clause 2.13.6).
                 * ((DNN/APN))
                 * Reference: 3GPP TS 29.272 7.3.36
                 */
                ret = fd_avp_search_avp(
                    avpch2, ogs_diam_service_selection, &avpch3);
                ogs_assert(ret == 0);
                if (avpch3) {
                    ret = fd_msg_avp_hdr(avpch3, &hdr);
                    session->name = ogs_strndup(
                                    (char*)hdr->avp_value->os.data,
                                    hdr->avp_value->os.len);
                    ogs_assert(session->name);
                } else {
                    ogs_error("no_Service-Selection");
                    error++;
                }

                /* AVP: 'Context-Identifier'(1423)
                 * The Context-Identifier in the APN-Configuration AVP shall
                 * identify that APN configuration, and it shall not have a
                 * value of zero. Furthermore, the Context-Identifier in the
                 * APN-Configuration AVP shall uniquely identify the EPS APN
                 * configuration per subscription.
                 * Reference: 3GPP TS 29.272 7.3.27
                 */
                ret = fd_avp_search_avp(avpch2,
                    ogs_diam_s6a_context_identifier, &avpch3);
                ogs_assert(ret == 0);
                if (avpch3) {
                    ret = fd_msg_avp_hdr(avpch3, &hdr);
                    session->context_identifier = hdr->avp_value->i32;
                } else {
                    ogs_error("no_Context-Identifier");
                    error++;
                }

                /* AVP: 'PDN-Type'(1456)
                 * The PDN-Type AVP indicates the address type of PDN.
                 * ((IPv4/IPv6/IPv4v6))
                 * Reference: 3GPP TS 29.272 7.3.62
                 */
                ret = fd_avp_search_avp(avpch2, ogs_diam_s6a_pdn_type,
                        &avpch3);
                ogs_assert(ret == 0);
                if (avpch3) {
                    ret = fd_msg_avp_hdr(avpch3, &hdr);
                    session->session_type =
                        OGS_PDU_SESSION_TYPE_FROM_DIAMETER(
                                hdr->avp_value->i32);
                } else {
                    ogs_error("no_PDN-Type");
                    error++;
                }

                /* AVP: '3GPP-Charging-Characteristics'(13)
                 * For GGSN, it contains the charging characteristics for 
                 * this PDP Context received in the Create PDP Context 
                 * Request Message (only available in R99 and later releases). 
                 * For PGW, it contains the charging characteristics for the 
                 * IP-CAN bearer.
                 * Reference: 3GPP TS 29.061 16.4.7.2 13
                 */
                ret = fd_avp_search_avp(avpch2, 
                        ogs_diam_s6a_3gpp_charging_characteristics, &avpch3);
                ogs_assert(ret == 0);
                if (avpch3) {
                    ret = fd_msg_avp_hdr(avpch3, &hdr);
                    ogs_ascii_to_hex(
                        (char*)hdr->avp_value->os.data,
                        (int)hdr->avp_value->os.len,
                        buf, sizeof(buf));
                    memcpy(session->charging_characteristics,
                            buf, OGS_CHRGCHARS_LEN);
                    session->charging_characteristics_presence = true;
                } else {
                    memcpy(session->charging_characteristics, 
                        (uint8_t *)"\x00\x00", OGS_CHRGCHARS_LEN);
                    session->charging_characteristics_presence = false;
                }

                /* AVP: 'Served-Party-IP-Address'(848)
                 * The Served-Party-IP-Address AVP holds the IP address of
                 * either the calling or called party, depending on whether
                 * the P-CSCF is in touch with the calling or the called
                 * party.
                 * ((UE IP STATIC ADDRESS))
                 * Reference: 32-299-f10
                 */
                ret = fd_msg_browse(avpch2, MSG_BRW_FIRST_CHILD,
                        &avpch3, NULL);
                ogs_assert(ret == 0);
                while (avpch3) {
                    ret = fd_msg_avp_hdr(avpch3, &hdr);
                    ogs_assert(ret == 0);
                    switch(hdr->avp_code) {
                    case OGS_DIAM_S6A_AVP_CODE_SERVED_PARTY_IP_ADDRESS:
                        ret = fd_msg_avp_value_interpret(avpch3, &addr.sa);
                        ogs_assert(ret == 0);

                        if (addr.ogs_sa_family == AF_INET) {
                            if (session->session_type ==
                                    OGS_PDU_SESSION_TYPE_IPV4) {
                                session->paa.addr =
                                    addr.sin.sin_addr.s_addr;
                            } else if (session->session_type ==
                                    OGS_PDU_SESSION_TYPE_IPV4V6) {
                                session->paa.both.addr =
                                    addr.sin.sin_addr.s_addr;
                            } else {
                                ogs_error("Warning: Received a static IPv4 "
                                    "address but PDN-Type does not include "
                                    "IPv4. Ignoring...");
                            }
                        } else if (addr.ogs_sa_family == AF_INET6) {
                            if (session->session_type ==
                                    OGS_PDU_SESSION_TYPE_IPV6) {
                                memcpy(session->paa.addr6,
                                    addr.sin6.sin6_addr.s6_addr,
                                    OGS_IPV6_LEN);
                            } else if (session->session_type ==
                                    OGS_PDU_SESSION_TYPE_IPV4V6) {
                                memcpy(session->paa.both.addr6,
                                    addr.sin6.sin6_addr.s6_addr,
                                    OGS_IPV6_LEN);
                            } else {
                                ogs_error("Warning: Received a static IPv6 "
                                    "address but PDN-Type does not include "
                                    "IPv6. Ignoring...");
                            }
                        } else {
                            ogs_error("Invalid family[%d]",
                                    addr.ogs_sa_family);
                        }
                        break;
                    default:
                        break;
                    }
                    fd_msg_browse(avpch3, MSG_BRW_NEXT, &avpch3, NULL);
                }

                /* AVP: 'EPS-Subscribed-QoS-Profile'(1431)
                 * The EPS-Subscribed-QoS-Profile AVP shall contain the
                 * bearer-level QoS parameters (QoS Class Identifier and
                 * Allocation Retention Priority) associated to the
                 * default bearer for an APN.
                 * Reference: 3GPP TS 29.272 7.3.37
                 */
                ret = fd_avp_search_avp(avpch2,
                    ogs_diam_s6a_eps_subscribed_qos_profile, &avpch3);
                ogs_assert(ret == 0);
                if (avpch3) {

                    /* AVP: 'QoS-Class-Identifier'(1028)
                     * The QoS-Class-Identifier AVP identifies a set of
                     * IP-CAN specific QoS parameters that define the
                     * authorized QoS, excluding the applicable bitrates
                     * and ARP for the IP-CAN bearer or service flow.
                     * Reference: 3GPP TS 29.212 7.3.37
                     */
                    ret = fd_avp_search_avp(avpch3,
                        ogs_diam_s6a_qos_class_identifier, &avpch4);
                    ogs_assert(ret == 0);
                    if (avpch4) {
                        ret = fd_msg_avp_hdr(avpch4, &hdr);
                        ogs_assert(ret == 0);
                        session->qos.index = hdr->avp_value->i32;
                    } else {
                        ogs_error("no_QoS-Class-Identifier");
                        error++;
                    }

                    /* AVP: 'Allocation-Retention-Priority'(1034)
                     * The Allocation-Retention-Priority AVP is used to
                     * indicate the priority of allocation and retention,
                     * the pre-emption capability and pre-emption
                     * vulnerability for the SDF if provided within the
                     * QoS-Information-AVP or for the EPS default bearer if
                     * provided within the Default-EPS-Bearer-QoS AVP.
                     * Reference: 3GPP TS 29.212 7.3.40
                     */
                    ret = fd_avp_search_avp(avpch3,
                        ogs_diam_s6a_allocation_retention_priority,
                        &avpch4);
                    ogs_assert(ret == 0);
                    if (avpch4) {

                        /* AVP: 'Priority-Level'(1046)
                         * The Priority-Level AVP is used for deciding
                         * whether a bearer establishment or modification
                         * request can be accepted or needs to be rejected
                         * in case of resource limitations.
                         * Reference: 3GPP TS 29.212 7.3.40
                         */
                        ret = fd_avp_search_avp(avpch4,
                            ogs_diam_s6a_priority_level, &avpch5);
                        ogs_assert(ret == 0);
                        if (avpch5) {
                            ret = fd_msg_avp_hdr(avpch5, &hdr);
                            ogs_assert(ret == 0);
                            session->qos.arp.priority_level =
                                hdr->avp_value->i32;
                        } else {
                            ogs_error("no_ARP");
                            error++;
                        }

                        /* AVP: 'Pre-emption-Capability'(1047)
                         * The Pre-emption-Capability AVP defines whether a
                         * service data flow can get resources that were
                         * already assigned to another service data flow
                         * with a lower priority level.
                         * Reference: 3GPP TS 29.212 7.3.40
                         */
                        ret = fd_avp_search_avp(avpch4,
                            ogs_diam_s6a_pre_emption_capability, &avpch5);
                        ogs_assert(ret == 0);
                        if (avpch5) {
                            ret = fd_msg_avp_hdr(avpch5, &hdr);
                            ogs_assert(ret == 0);
                            session->qos.arp.pre_emption_capability =
                                hdr->avp_value->i32;
                        } else {
                            session->qos.arp.pre_emption_capability =
                                OGS_EPC_PRE_EMPTION_DISABLED;
                        }

                        /* AVP: 'Pre-emption-Vulnerability'(1048)
                         * The Pre-emption-Vulnerability AVP defines whether
                         * a service data flow can lose the resources
                         * assigned to it in order to admit a service data
                         * flow with higher priority level.
                         * Reference: 3GPP TS 29.212 7.3.40
                         */
                        ret = fd_avp_search_avp(avpch4,
                            ogs_diam_s6a_pre_emption_vulnerability,
                            &avpch5);
                        ogs_assert(ret == 0);
                        if (avpch5) {
                            ret = fd_msg_avp_hdr(avpch5, &hdr);
                            ogs_assert(ret == 0);
                            session->qos.arp.pre_emption_vulnerability =
                                hdr->avp_value->i32;
                        } else {
                            session->qos.arp.pre_emption_vulnerability =
                                OGS_EPC_PRE_EMPTION_ENABLED;
                        }

                    } else {
                        ogs_error("no_QCI");
                        error++;
                    }
                } else {
                    ogs_error("no_EPS-Subscribed-QoS-Profile");
                    error++;
                }

                /* AVP: 'MIP6-Agent-Info'(486)
                 * The MIP6-Agent-Info AVP contains necessary information
                 * to assign an HA to the MN. When the MIP6-Agent-Info AVP
                 * is present in a message, it MUST contain either the
                 * MIP-Home-Agent-Address AVP, the MIP-Home-Agent-Host AVP,
                 * or both AVPs.
                 * Reference: 3GPP TS 29.212 7.3.45
                 */
                ret = fd_avp_search_avp(avpch2,
                        ogs_diam_mip6_agent_info, &avpch3);
                ogs_assert(ret == 0);
                if (avpch3) {

                    /* AVP: 'MIP-Home-Agent-Address'(334)
                     * The MIP-Home-Agent-Host AVP contains the identity of
                     * the assigned MIPv6 HA. Both the Destination-Realm and
                     * the Destination-Host AVPs of the HA are included in
                     * the grouped AVP. The usage of the MIP-Home-Agent-Host
                     * AVP is equivalent to the MIP-Home-Agent-Address AVP
                     * but offers an additional level of indirection by
                     * using the DNS infrastructure. The Destination-Host
                     * AVP is used to identify an HA, and the Destination-
                      * Realm AVP is used to identify the realm where the HA
                     * is located.
                     * ((SMF IP STATIC ADDRESS))
                     * Reference: 3GPP TS 29.212 7.3.42
                     */
                    ret = fd_msg_browse(avpch3,
                        MSG_BRW_FIRST_CHILD, &avpch4, NULL);
                    ogs_assert(ret == 0);
                    while (avpch4) {
                        ret = fd_msg_avp_hdr(avpch4, &hdr);
                        switch(hdr->avp_code) {
                        case OGS_DIAM_S6A_AVP_CODE_MIP_HOME_AGENT_ADDRESS:
                            ret = fd_msg_avp_value_interpret(avpch4,
                                    &addr.sa);
                            ogs_assert(ret == 0);
                            if (addr.ogs_sa_family == AF_INET)
                            {
                                session->smf_ip.ipv4 = 1;
                                session->smf_ip.addr =
                                    addr.sin.sin_addr.s_addr;
                            }
                            else if (addr.ogs_sa_family == AF_INET6)
                            {
                                session->smf_ip.ipv6 = 1;
                                memcpy(session->smf_ip.addr6,
                                    addr.sin6.sin6_addr.s6_addr,
                                    OGS_IPV6_LEN);
                            }
                            else
                            {
                                ogs_error("Invald family:%d",
                                        addr.ogs_sa_family);
                                error++;
                            }
                            break;
                        default:
                            ogs_error("Unknown AVP-Code:%d",
                                    hdr->avp_code);
                            error++;
                            break; 
                        }
                        fd_msg_browse(avpch4, MSG_BRW_NEXT,
                                &avpch4, NULL);
                    }
                }

                /* AVP: 'AMBR'(1435)
                 * The Amber AVP contains the Max-Requested-Bandwidth-UL
                 * and Max-Requested-Bandwidth-DL AVPs.
                 * Reference: 3GPP TS 29.272 7.3.41
                 */
                ret = fd_avp_search_avp(avpch2, ogs_diam_s6a_ambr, &avpch3);
                ogs_assert(ret == 0);
                if (avpch3) {

                /* AVP: 'Max-Requested-Bandwidth-UL'(516)
                 * The Max -Bandwidth-UL AVP indicates the maximum
                 * requested bandwidth in bits per second for an uplink
                 * IP flow.
                 * Reference: 3GPP TS 29.214 7.3.41
                 */
                    ret = fd_avp_search_avp(avpch3,
                        ogs_diam_s6a_max_bandwidth_ul, &avpch4);
                    ogs_assert(ret == 0);
                    if (avpch4) {
                        ret = fd_msg_avp_hdr(avpch4, &hdr);
                        ogs_assert(ret == 0);
                        session->ambr.uplink = hdr->avp_value->u32;
                    } else {
                        ogs_error("no_Max-Bandwidth-UL");
                        error++;
                    }

                    /* AVP: 'Max-Requested-Bandwidth-DL'(515)
                     * The Max-Requested-Bandwidth-DL AVP indicates the
                     * maximum bandwidth in bits per second for a downlink
                     * IP flow.
                     * Reference: 3GPP TS 29.214 7.3.41
                     */
                    ret = fd_avp_search_avp(avpch3,
                        ogs_diam_s6a_max_bandwidth_dl, &avpch4);
                    ogs_assert(ret == 0);
                    if (avpch4) {
                        ret = fd_msg_avp_hdr(avpch4, &hdr);
                        ogs_assert(ret == 0);
                        session->ambr.downlink = hdr->avp_value->u32;
                    } else {
                        ogs_error("no_Max-Bandwidth-DL");
                        error++;
                    }
                }

                slice_data->num_of_session++;
                break;
            }
            default:
                ogs_warn("Unknown AVP-code:%d", hdr->avp_code);
                break;
            }

            fd_msg_browse(avpch2, MSG_BRW_NEXT, &avpch2, NULL);
        }

        if (slice_data->num_of_session)
            subscription_data->num_of_slice = 1;
        *subdatamask = (*subdatamask | OGS_DIAM_S6A_SUBDATA_APN_CONFIG);
    }

    return error;
}

/* MME Sends Authentication Information Request to HSS */
void mme_s6a_send_air(mme_ue_t *mme_ue,
    ogs_nas_authentication_failure_parameter_t
        *authentication_failure_parameter)
{
    int ret;

    struct msg *req = NULL;
    struct avp *avp;
    struct avp *avpch;
    union avp_value val;
    struct sess_state *sess_data = NULL, *svg;
    struct session *session = NULL;
    ogs_nas_plmn_id_t nas_plmn_id;

    uint8_t resync[OGS_AUTS_LEN + OGS_RAND_LEN];

    ogs_assert(mme_ue);

    ogs_debug("[MME] Authentication-Information-Request");

    /* Clear Security Context */
    CLEAR_SECURITY_CONTEXT(mme_ue);

    /* Create the random value to store with the session */
    sess_data = ogs_calloc(1, sizeof (*sess_data));
    ogs_assert(sess_data);

    sess_data->mme_ue = mme_ue;

    /* Create the request */
    ret = fd_msg_new(ogs_diam_s6a_cmd_air, MSGFL_ALLOC_ETEID, &req);
    ogs_assert(ret == 0);

    /* Create a new session */
    #define OGS_DIAM_S6A_APP_SID_OPT  "app_s6a"
    ret = fd_msg_new_session(req, (os0_t)OGS_DIAM_S6A_APP_SID_OPT, 
            CONSTSTRLEN(OGS_DIAM_S6A_APP_SID_OPT));
    ogs_assert(ret == 0);
    ret = fd_msg_sess_get(fd_g_config->cnf_dict, req, &session, NULL);
    ogs_assert(ret == 0);

    /* Set the Auth-Session-State AVP */
    ret = fd_msg_avp_new(ogs_diam_auth_session_state, 0, &avp);
    ogs_assert(ret == 0);
    val.i32 = OGS_DIAM_AUTH_SESSION_NO_STATE_MAINTAINED;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set Origin-Host & Origin-Realm */
    ret = fd_msg_add_origin(req, 0);
    ogs_assert(ret == 0);

    /* Set the Destination-Realm AVP */
    ret = fd_msg_avp_new(ogs_diam_destination_realm, 0, &avp);
    ogs_assert(ret == 0);
    val.os.data = (unsigned char *)(fd_g_config->cnf_diamrlm);
    val.os.len  = strlen(fd_g_config->cnf_diamrlm);
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set the User-Name AVP */
    ret = fd_msg_avp_new(ogs_diam_user_name, 0, &avp);
    ogs_assert(ret == 0);
    val.os.data = (uint8_t *)mme_ue->imsi_bcd;
    val.os.len = strlen(mme_ue->imsi_bcd);
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Add the Authentication-Info */
    ret = fd_msg_avp_new(ogs_diam_s6a_req_eutran_auth_info, 0, &avp);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_new(ogs_diam_s6a_number_of_requested_vectors, 0, &avpch);
    ogs_assert(ret == 0);
    val.u32 = 1;
    ret = fd_msg_avp_setvalue (avpch, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add (avp, MSG_BRW_LAST_CHILD, avpch);
    ogs_assert(ret == 0);

    ret = fd_msg_avp_new(ogs_diam_s6a_immediate_response_preferred, 0, &avpch);
    ogs_assert(ret == 0);
    val.u32 = 1;
    ret = fd_msg_avp_setvalue(avpch, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(avp, MSG_BRW_LAST_CHILD, avpch);
    ogs_assert(ret == 0);

    if (authentication_failure_parameter) {
        ret = fd_msg_avp_new(ogs_diam_s6a_re_synchronization_info, 0, &avpch);
        ogs_assert(ret == 0);
        memcpy(resync, mme_ue->rand, OGS_RAND_LEN);
        memcpy(resync+OGS_RAND_LEN,
                authentication_failure_parameter->auts, OGS_AUTS_LEN);
        val.os.len = OGS_RAND_LEN+OGS_AUTS_LEN;
        val.os.data = resync;
        ret = fd_msg_avp_setvalue(avpch, &val);
        ogs_assert(ret == 0);
        ret = fd_msg_avp_add(avp, MSG_BRW_LAST_CHILD, avpch);
        ogs_assert(ret == 0);
    }

    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set the Visited-PLMN-Id AVP */
    ret = fd_msg_avp_new(ogs_diam_visited_plmn_id, 0, &avp);
    ogs_assert(ret == 0);
    val.os.data = ogs_nas_from_plmn_id(&nas_plmn_id, &mme_ue->tai.plmn_id);
    val.os.len  = OGS_PLMN_ID_LEN;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set Vendor-Specific-Application-Id AVP */
    ret = ogs_diam_message_vendor_specific_appid_set(
            req, OGS_DIAM_S6A_APPLICATION_ID);
    ogs_assert(ret == 0);
    
    ret = clock_gettime(CLOCK_REALTIME, &sess_data->ts);
    ogs_assert(ret == 0);

    /* Keep a pointer to the session data for debug purpose,
     * in real life we would not need it */
    svg = sess_data;

    /* Store this value in the session */
    ret = fd_sess_state_store(mme_s6a_reg, session, &sess_data);
    ogs_assert(ret == 0);
    ogs_assert(sess_data == 0);

    /* Send the request */
    ret = fd_msg_send(&req, mme_s6a_aia_cb, svg);
    ogs_assert(ret == 0);

    /* Increment the counter */
    ogs_assert(pthread_mutex_lock(&ogs_diam_logger_self()->stats_lock) == 0);
    ogs_diam_logger_self()->stats.nb_sent++;
    ogs_assert(pthread_mutex_unlock(&ogs_diam_logger_self()->stats_lock) == 0);
}

/* MME received Authentication Information Answer from HSS */
static void mme_s6a_aia_cb(void *data, struct msg **msg)
{
    int ret;
    
    struct sess_state *sess_data = NULL;
    struct timespec ts;
    struct session *session;
    struct avp *avp, *avpch;
    struct avp *avp_e_utran_vector, *avp_xres, *avp_kasme, *avp_rand, *avp_autn;
    struct avp_hdr *hdr;
    unsigned long dur;
    int error = 0;
    int new;

    mme_event_t *e = NULL;
    mme_ue_t *mme_ue = NULL;
    ogs_diam_s6a_message_t *s6a_message = NULL;
    ogs_diam_s6a_aia_message_t *aia_message = NULL;
    ogs_diam_e_utran_vector_t *e_utran_vector = NULL;

    ogs_debug("[MME] Authentication-Information-Answer");
    
    ret = clock_gettime(CLOCK_REALTIME, &ts);
    ogs_assert(ret == 0);

    /* Search the session, retrieve its data */
    ret = fd_msg_sess_get(fd_g_config->cnf_dict, *msg, &session, &new);
    if (ret != 0) {
        ogs_error("fd_msg_sess_get() failed");
        return;
    }
    if (new != 0) {
        ogs_error("fd_msg_sess_get() failed");
        return;
    }
    
    ret = fd_sess_state_retrieve(mme_s6a_reg, session, &sess_data);
    if (ret != 0) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }
    if (!sess_data) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }
    if ((void *)sess_data != data) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }

    mme_ue = sess_data->mme_ue;
    ogs_assert(mme_ue);

    /* Set Authentication-Information Command */
    s6a_message = ogs_calloc(1, sizeof(ogs_diam_s6a_message_t));
    ogs_assert(s6a_message);
    s6a_message->cmd_code = OGS_DIAM_S6A_CMD_CODE_AUTHENTICATION_INFORMATION;
    aia_message = &s6a_message->aia_message;
    ogs_assert(aia_message);
    e_utran_vector = &aia_message->e_utran_vector;
    ogs_assert(e_utran_vector);
    
    /* Value of Result Code */
    ret = fd_msg_search_avp(*msg, ogs_diam_result_code, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        s6a_message->result_code = hdr->avp_value->i32;
        s6a_message->err = &s6a_message->result_code;
        ogs_debug("    Result Code: %d", hdr->avp_value->i32);
    } else {
        ret = fd_msg_search_avp(*msg, ogs_diam_experimental_result, &avp);
        ogs_assert(ret == 0);
        if (avp) {
            ret = fd_avp_search_avp(
                    avp, ogs_diam_experimental_result_code, &avpch);
            ogs_assert(ret == 0);
            if (avpch) {
                ret = fd_msg_avp_hdr(avpch, &hdr);
                ogs_assert(ret == 0);
                s6a_message->result_code = hdr->avp_value->i32;
                s6a_message->exp_err = &s6a_message->result_code;
                ogs_debug("    Experimental Result Code: %d",
                        s6a_message->result_code);
            }
        } else {
            ogs_error("no Result-Code");
            error++;
        }
    }

    /* Value of Origin-Host */
    ret = fd_msg_search_avp(*msg, ogs_diam_origin_host, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        ogs_debug("    From '%.*s'",
                (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
    } else {
        ogs_error("no_Origin-Host ");
        error++;
    }

    /* Value of Origin-Realm */
    ret = fd_msg_search_avp(*msg, ogs_diam_origin_realm, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        ogs_debug("         ('%.*s')",
                (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
    } else {
        ogs_error("no_Origin-Realm ");
        error++;
    }

    if (s6a_message->result_code != ER_DIAMETER_SUCCESS) {
        if (s6a_message->err)
            ogs_info("    Result Code: %d", s6a_message->result_code);
        else if (s6a_message->exp_err)
            ogs_info("    Experimental Result Code: %d",
                    s6a_message->result_code);
        else {
            ogs_fatal("ERROR DIAMETER Result Code(%d)",
                    s6a_message->result_code);
            ogs_assert_if_reached();
        }
        goto out;
    }

    ret = fd_msg_search_avp(*msg, ogs_diam_s6a_authentication_info, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
    } else {
        ogs_error("no_Authentication-Info ");
        error++;
    }

    ret = fd_avp_search_avp(
            avp, ogs_diam_s6a_e_utran_vector, &avp_e_utran_vector);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp_e_utran_vector, &hdr);
        ogs_assert(ret == 0);
    } else {
        ogs_error("no_E-UTRAN-Vector-Info ");
        error++;
    }

    ret = fd_avp_search_avp(avp_e_utran_vector, ogs_diam_s6a_xres, &avp_xres);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp_xres, &hdr);
        ogs_assert(ret == 0);
        memcpy(e_utran_vector->xres,
                hdr->avp_value->os.data, hdr->avp_value->os.len);
        e_utran_vector->xres_len = hdr->avp_value->os.len;
    } else {
        ogs_error("no_XRES");
        error++;
    }

    ret = fd_avp_search_avp(avp_e_utran_vector, ogs_diam_s6a_kasme, &avp_kasme);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp_kasme, &hdr);
        ogs_assert(ret == 0);
        memcpy(e_utran_vector->kasme,
                hdr->avp_value->os.data, hdr->avp_value->os.len);
    } else {
        ogs_error("no_KASME");
        error++;
    }


    ret = fd_avp_search_avp(avp_e_utran_vector, ogs_diam_s6a_rand, &avp_rand);
    if (avp) {
        ret = fd_msg_avp_hdr(avp_rand, &hdr);
        memcpy(e_utran_vector->rand,
                hdr->avp_value->os.data, hdr->avp_value->os.len);
    } else {
        ogs_error("no_RAND");
        error++;
    }

    ret = fd_avp_search_avp(avp_e_utran_vector, ogs_diam_s6a_autn, &avp_autn);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp_autn, &hdr);
        ogs_assert(ret == 0);
        memcpy(e_utran_vector->autn,
                hdr->avp_value->os.data, hdr->avp_value->os.len);
    } else {
        ogs_error("no_AUTN");
        error++;
    }

out:
    if (!error) {
        int rv;
        e = mme_event_new(MME_EVENT_S6A_MESSAGE);
        ogs_assert(e);
        e->mme_ue = mme_ue;
        e->s6a_message = s6a_message;
        rv = ogs_queue_push(ogs_app()->queue, e);
        if (rv != OGS_OK) {
            ogs_error("ogs_queue_push() failed:%d", (int)rv);
            ogs_free(s6a_message);
            mme_event_free(e);
        } else {
            ogs_pollset_notify(ogs_app()->pollset);
        }
    }

    /* Free the message */
    ogs_assert(pthread_mutex_lock(&ogs_diam_logger_self()->stats_lock) == 0);
    dur = ((ts.tv_sec - sess_data->ts.tv_sec) * 1000000) + 
        ((ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);
    if (ogs_diam_logger_self()->stats.nb_recv) {
        /* Ponderate in the avg */
        ogs_diam_logger_self()->stats.avg = (ogs_diam_logger_self()->stats.avg * 
            ogs_diam_logger_self()->stats.nb_recv + dur) /
            (ogs_diam_logger_self()->stats.nb_recv + 1);
        /* Min, max */
        if (dur < ogs_diam_logger_self()->stats.shortest)
            ogs_diam_logger_self()->stats.shortest = dur;
        if (dur > ogs_diam_logger_self()->stats.longest)
            ogs_diam_logger_self()->stats.longest = dur;
    } else {
        ogs_diam_logger_self()->stats.shortest = dur;
        ogs_diam_logger_self()->stats.longest = dur;
        ogs_diam_logger_self()->stats.avg = dur;
    }
    if (error)
        ogs_diam_logger_self()->stats.nb_errs++;
    else 
        ogs_diam_logger_self()->stats.nb_recv++;

    ogs_assert(pthread_mutex_unlock(&ogs_diam_logger_self()->stats_lock) == 0);
    
    /* Display how long it took */
    if (ts.tv_nsec > sess_data->ts.tv_nsec)
        ogs_trace("in %d.%06ld sec", 
                (int)(ts.tv_sec - sess_data->ts.tv_sec),
                (long)(ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);
    else
        ogs_trace("in %d.%06ld sec", 
                (int)(ts.tv_sec + 1 - sess_data->ts.tv_sec),
                (long)(1000000000 + ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);
    
    ret = fd_msg_free(*msg);
    ogs_assert(ret == 0);
    *msg = NULL;

    state_cleanup(sess_data, NULL, NULL);
    return;
}

/* MME Sends Update Location Request to HSS */
void mme_s6a_send_ulr(mme_ue_t *mme_ue)
{
    int ret;

    struct msg *req = NULL;
    struct avp *avp, *avpch;
    union avp_value val;
    struct sess_state *sess_data = NULL, *svg;
    struct session *session = NULL;
    ogs_nas_plmn_id_t nas_plmn_id;

    ogs_assert(mme_ue);

    ogs_debug("[MME] Update-Location-Request");

    /* Create the random value to store with the session */
    sess_data = ogs_calloc(1, sizeof(*sess_data));
    ogs_assert(sess_data);
    sess_data->mme_ue = mme_ue;

    /* Create the request */
    ret = fd_msg_new(ogs_diam_s6a_cmd_ulr, MSGFL_ALLOC_ETEID, &req);
    ogs_assert(ret == 0);

    /* Create a new session */
    #define OGS_DIAM_S6A_APP_SID_OPT  "app_s6a"
    ret = fd_msg_new_session(req, (os0_t)OGS_DIAM_S6A_APP_SID_OPT, 
            CONSTSTRLEN(OGS_DIAM_S6A_APP_SID_OPT));
    ogs_assert(ret == 0);
    ret = fd_msg_sess_get(fd_g_config->cnf_dict, req, &session, NULL);
    ogs_assert(ret == 0);

    /* Set the Auth-Session-State AVP */
    ret = fd_msg_avp_new(ogs_diam_auth_session_state, 0, &avp);
    ogs_assert(ret == 0);
    val.i32 = OGS_DIAM_AUTH_SESSION_NO_STATE_MAINTAINED;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set Origin-Host & Origin-Realm */
    ret = fd_msg_add_origin(req, 0);
    ogs_assert(ret == 0);

    /* Set the Destination-Realm AVP */
    ret = fd_msg_avp_new(ogs_diam_destination_realm, 0, &avp);
    ogs_assert(ret == 0);
    val.os.data = (unsigned char *)(fd_g_config->cnf_diamrlm);
    val.os.len  = strlen(fd_g_config->cnf_diamrlm);
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set the User-Name AVP */
    ret = fd_msg_avp_new(ogs_diam_user_name, 0, &avp);
    ogs_assert(ret == 0);
    val.os.data = (uint8_t *)mme_ue->imsi_bcd;
    val.os.len  = strlen(mme_ue->imsi_bcd);
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set the Terminal-Information AVP */
    if (mme_ue->imeisv_len) {
        ret = fd_msg_avp_new(ogs_diam_s6a_terminal_information, 0, &avp);
        ogs_assert(ret == 0);

        ret = fd_msg_avp_new(ogs_diam_s6a_imei, 0, &avpch);
        ogs_assert(ret == 0);
        val.os.data = (uint8_t *)mme_ue->imeisv_bcd;
        val.os.len  = 14;
        ret = fd_msg_avp_setvalue(avpch, &val);
        ogs_assert(ret == 0);
        ret = fd_msg_avp_add(avp, MSG_BRW_LAST_CHILD, avpch);
        ogs_assert(ret == 0);

        ret = fd_msg_avp_new(ogs_diam_s6a_software_version, 0, &avpch);
        ogs_assert(ret == 0);
        val.os.data = (uint8_t *)mme_ue->imeisv_bcd+14;
        val.os.len  = 2;
        ret = fd_msg_avp_setvalue(avpch, &val);
        ogs_assert(ret == 0);
        ret = fd_msg_avp_add(avp, MSG_BRW_LAST_CHILD, avpch);
        ogs_assert(ret == 0);

        ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
        ogs_assert(ret == 0);
    }

    /* Set the RAT-Type */
    ret = fd_msg_avp_new(ogs_diam_rat_type, 0, &avp);
    ogs_assert(ret == 0);
    val.u32 = OGS_DIAM_RAT_TYPE_EUTRAN;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set the ULR-Flags */
    ret = fd_msg_avp_new(ogs_diam_s6a_ulr_flags, 0, &avp);
    ogs_assert(ret == 0);
    val.u32 = OGS_DIAM_S6A_ULR_S6A_S6D_INDICATOR;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set the Visited-PLMN-Id */
    ret = fd_msg_avp_new(ogs_diam_visited_plmn_id, 0, &avp);
    ogs_assert(ret == 0);
    val.os.data = ogs_nas_from_plmn_id(&nas_plmn_id, &mme_ue->tai.plmn_id);
    val.os.len  = OGS_PLMN_ID_LEN;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set the UE-SRVCC Capability */
    ret = fd_msg_avp_new(ogs_diam_s6a_ue_srvcc_capability, 0, &avp);
    ogs_assert(ret == 0);
    val.u32 = OGS_DIAM_S6A_UE_SRVCC_NOT_SUPPORTED;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set Vendor-Specific-Application-Id AVP */
    ret = ogs_diam_message_vendor_specific_appid_set(
            req, OGS_DIAM_S6A_APPLICATION_ID);
    ogs_assert(ret == 0);

    ret = clock_gettime(CLOCK_REALTIME, &sess_data->ts);
    ogs_assert(ret == 0);

    /* Keep a pointer to the session data for debug purpose,
     * in real life we would not need it */
    svg = sess_data;

    /* Store this value in the session */
    ret = fd_sess_state_store(mme_s6a_reg, session, &sess_data); 
    ogs_assert(ret == 0);
    ogs_assert(sess_data == 0);

    /* Send the request */
    ret = fd_msg_send(&req, mme_s6a_ula_cb, svg);
    ogs_assert(ret == 0);

    /* Increment the counter */
    ogs_assert(pthread_mutex_lock(&ogs_diam_logger_self()->stats_lock) == 0);
    ogs_diam_logger_self()->stats.nb_sent++;
    ogs_assert(pthread_mutex_unlock(&ogs_diam_logger_self()->stats_lock) == 0);
}

/* MME Sends Purge UE Request to HSS */
void mme_s6a_send_pur(mme_ue_t *mme_ue)
{
    int ret;

    struct msg *req = NULL;
    struct avp *avp;
    union avp_value val;
    struct sess_state *sess_data = NULL, *svg;
    struct session *session = NULL;

    ogs_assert(mme_ue);

    ogs_debug("[MME] Purge-UE-Request");

    /* Create the random value to store with the session */
    sess_data = ogs_calloc(1, sizeof(*sess_data));
    ogs_assert(sess_data);
    sess_data->mme_ue = mme_ue;

    /* Create the request */
    ret = fd_msg_new(ogs_diam_s6a_cmd_pur, MSGFL_ALLOC_ETEID, &req);
    ogs_assert(ret == 0);

    /* Create a new session */
    #define OGS_DIAM_S6A_APP_SID_OPT  "app_s6a"
    ret = fd_msg_new_session(req, (os0_t)OGS_DIAM_S6A_APP_SID_OPT, 
            CONSTSTRLEN(OGS_DIAM_S6A_APP_SID_OPT));
    ogs_assert(ret == 0);
    ret = fd_msg_sess_get(fd_g_config->cnf_dict, req, &session, NULL);
    ogs_assert(ret == 0);

    /* Set the Auth-Session-State AVP */
    ret = fd_msg_avp_new(ogs_diam_auth_session_state, 0, &avp);
    ogs_assert(ret == 0);
    val.i32 = OGS_DIAM_AUTH_SESSION_NO_STATE_MAINTAINED;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set Origin-Host & Origin-Realm */
    ret = fd_msg_add_origin(req, 0);
    ogs_assert(ret == 0);

    /* Set the Destination-Realm AVP */
    ret = fd_msg_avp_new(ogs_diam_destination_realm, 0, &avp);
    ogs_assert(ret == 0);
    val.os.data = (unsigned char *)(fd_g_config->cnf_diamrlm);
    val.os.len  = strlen(fd_g_config->cnf_diamrlm);
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set the User-Name AVP */
    ret = fd_msg_avp_new(ogs_diam_user_name, 0, &avp);
    ogs_assert(ret == 0);
    val.os.data = (uint8_t *)mme_ue->imsi_bcd;
    val.os.len  = strlen(mme_ue->imsi_bcd);
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(req, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set Vendor-Specific-Application-Id AVP */
    ret = ogs_diam_message_vendor_specific_appid_set(
            req, OGS_DIAM_S6A_APPLICATION_ID);
    ogs_assert(ret == 0);

    ret = clock_gettime(CLOCK_REALTIME, &sess_data->ts);
    ogs_assert(ret == 0);

    /* Keep a pointer to the session data for debug purpose,
     * in real life we would not need it */
    svg = sess_data;

    /* Store this value in the session */
    ret = fd_sess_state_store(mme_s6a_reg, session, &sess_data);
    ogs_assert(ret == 0);
    ogs_assert(sess_data == 0);

    /* Send the request */
    ret = fd_msg_send(&req, mme_s6a_pua_cb, svg);
    ogs_assert(ret == 0);

    /* Increment the counter */
    ogs_assert(pthread_mutex_lock(&ogs_diam_logger_self()->stats_lock) == 0);
    ogs_diam_logger_self()->stats.nb_sent++;
    ogs_assert(pthread_mutex_unlock(&ogs_diam_logger_self()->stats_lock) == 0);
}

/* MME received Update Location Answer from HSS */
static void mme_s6a_ula_cb(void *data, struct msg **msg)
{
    int ret;

    struct sess_state *sess_data = NULL;
    struct timespec ts;
    struct session *session;
    struct avp *avp, *avpch;
    struct avp_hdr *hdr;
    unsigned long dur;
    int error = 0;
    int new;

    mme_event_t *e = NULL;
    mme_ue_t *mme_ue = NULL;
    ogs_diam_s6a_message_t *s6a_message = NULL;
    ogs_diam_s6a_ula_message_t *ula_message = NULL;
    ogs_subscription_data_t *subscription_data = NULL;

    ogs_debug("[MME] Update-Location-Answer");

    ret = clock_gettime(CLOCK_REALTIME, &ts);
    ogs_assert(ret == 0);

    /* Search the session, retrieve its data */
    ret = fd_msg_sess_get(fd_g_config->cnf_dict, *msg, &session, &new);
    if (ret != 0) {
        ogs_error("fd_msg_sess_get() failed");
        return;
    }
    if (new != 0) {
        ogs_error("fd_msg_sess_get() failed");
        return;
    }
    
    ret = fd_sess_state_retrieve(mme_s6a_reg, session, &sess_data);
    if (ret != 0) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }
    if (!sess_data) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }
    if ((void *)sess_data != data) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }

    mme_ue = sess_data->mme_ue;
    ogs_assert(mme_ue);

    /* Set Update-Location Command */
    s6a_message = ogs_calloc(1, sizeof(ogs_diam_s6a_message_t));
    ogs_assert(s6a_message);
    s6a_message->cmd_code = OGS_DIAM_S6A_CMD_CODE_UPDATE_LOCATION;
    ula_message = &s6a_message->ula_message;
    ogs_assert(ula_message);
    subscription_data = &ula_message->subscription_data;
    ogs_assert(subscription_data);

    /* AVP: 'Result-Code'(268)
     * The Result-Code AVP indicates whether a particular request was completed
     * successfully or whether an error occurred. The Result-Code data field
     * contains an IANA-managed 32-bit address space representing errors.
     * Reference: RFC 6733
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_result_code, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        s6a_message->result_code = hdr->avp_value->i32;
        s6a_message->err = &s6a_message->result_code;
        ogs_debug("    Result Code: %d", hdr->avp_value->i32);
    } else {
        ret = fd_msg_search_avp(*msg, ogs_diam_experimental_result, &avp);
        ogs_assert(ret == 0);
        if (avp) {
            ret = fd_avp_search_avp(avp,
                    ogs_diam_experimental_result_code, &avpch);
            ogs_assert(ret == 0);
            if (avpch) {
                ret = fd_msg_avp_hdr(avpch, &hdr);
                ogs_assert(ret == 0);
                s6a_message->result_code = hdr->avp_value->i32;
                s6a_message->exp_err = &s6a_message->result_code;
                ogs_debug("    Experimental Result Code: %d",
                        s6a_message->result_code);
            }
        } else {
            ogs_error("no Result-Code");
            error++;
        }
    }

    /* AVP: 'Origin-Host'(264)
     * The Origin-Host AVP identifies the endpoint that originated the Diameter
     * message. Relay agents MUST NOT modify this AVP. The value of the
     * Origin-Host AVP is guaranteed to be unique within a single host.
     * Reference: RFC 6733
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_origin_host, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        ogs_debug("    From '%.*s'",
                (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
    } else {
        ogs_error("no_Origin-Host");
        error++;
    }

    /* AVP: 'Origin-Realm'(296)
     * This AVP contains the Realm of the originator of any Diameter message
     * and MUST be present in all messages. This AVP SHOULD be placed as close
     * to the Diameter header as possible.
     * Reference: RFC 6733
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_origin_realm, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        ogs_debug("         ('%.*s')",
                (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
    } else {
        ogs_error("no_Origin-Realm");
        error++;
    }

    /* AVP: 'ULA-Flags'(1406)
     * The ULA-Flags AVP contains a bit mask, whose meanings are defined in
     * table in 29.272 7.3.8/1.
     * Reference: 3GPP TS 29.272-f70
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_s6a_ula_flags, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        ula_message->ula_flags = hdr->avp_value->i32;
    } else {
        ogs_error("no_ULA-Flags");
        error++;
    }

    /* AVP: 'Subscription-Data'(1400)
     * The Subscription-Data AVP contains the information related to the user
     * profile relevant for EPS and GERAN/UTRAN.
     * Reference: 3GPP TS 29.272-f70
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_s6a_subscription_data, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        uint32_t subdatamask = 0;
        ret = mme_s6a_subscription_data_from_avp(avp, subscription_data, mme_ue,
            &subdatamask);

        if (!(subdatamask & OGS_DIAM_S6A_SUBDATA_NAM)) {
            mme_ue->network_access_mode = 0;
            ogs_warn("no subscribed Network-Access-Mode, defaulting to "
                "PACKET_AND_CIRCUIT (0)");
        }
        if (!(subdatamask & OGS_DIAM_S6A_SUBDATA_CC)) {
            memcpy(mme_ue->charging_characteristics, (uint8_t *)"\x00\x00", 
                OGS_CHRGCHARS_LEN);
            mme_ue->charging_characteristics_presence = false;
        }
        if (!(subdatamask & OGS_DIAM_S6A_SUBDATA_UEAMBR)) {
            ogs_error("no_AMBR");
            error++;
        }
        if (!(subdatamask & OGS_DIAM_S6A_SUBDATA_RAU_TAU_TIMER)) {
            subscription_data->subscribed_rau_tau_timer =
                OGS_RAU_TAU_DEFAULT_TIME;
        }
        if (!(subdatamask & OGS_DIAM_S6A_SUBDATA_APN_CONFIG)) {
            ogs_error("no_APN-Configuration-Profile");
            error++;
        }
    } else {
        ogs_error("no_Subscription-Data");
        error++;
    }

    if (!error) {
        int rv;
        e = mme_event_new(MME_EVENT_S6A_MESSAGE);
        ogs_assert(e);
        e->mme_ue = mme_ue;
        e->s6a_message = s6a_message;
        rv = ogs_queue_push(ogs_app()->queue, e);
        if (rv != OGS_OK) {
            ogs_error("ogs_queue_push() failed:%d", (int)rv);
            ogs_subscription_data_free(subscription_data);
            ogs_free(s6a_message);
            mme_event_free(e);
        } else {
            ogs_pollset_notify(ogs_app()->pollset);
        }
    } else {
        ogs_subscription_data_free(subscription_data);
        ogs_free(s6a_message);
    }

    /* Free the message */
    ogs_assert(pthread_mutex_lock(&ogs_diam_logger_self()->stats_lock) == 0);
    dur = ((ts.tv_sec - sess_data->ts.tv_sec) * 1000000) +
        ((ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);
    if (ogs_diam_logger_self()->stats.nb_recv) {
        /* Ponderate in the avg */
        ogs_diam_logger_self()->stats.avg =
            (ogs_diam_logger_self()->stats.avg *
            ogs_diam_logger_self()->stats.nb_recv + dur) /
            (ogs_diam_logger_self()->stats.nb_recv + 1);
        /* Min, max */
        if (dur < ogs_diam_logger_self()->stats.shortest)
            ogs_diam_logger_self()->stats.shortest = dur;
        if (dur > ogs_diam_logger_self()->stats.longest)
            ogs_diam_logger_self()->stats.longest = dur;
    } else {
        ogs_diam_logger_self()->stats.shortest = dur;
        ogs_diam_logger_self()->stats.longest = dur;
        ogs_diam_logger_self()->stats.avg = dur;
    }
    if (error)
        ogs_diam_logger_self()->stats.nb_errs++;
    else 
        ogs_diam_logger_self()->stats.nb_recv++;

    ogs_assert(pthread_mutex_unlock(&ogs_diam_logger_self()->stats_lock) == 0);

    /* Display how long it took */
    if (ts.tv_nsec > sess_data->ts.tv_nsec)
        ogs_trace("in %d.%06ld sec",
                (int)(ts.tv_sec - sess_data->ts.tv_sec),
                (long)(ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);
    else
        ogs_trace("in %d.%06ld sec",
                (int)(ts.tv_sec + 1 - sess_data->ts.tv_sec),
                (long)(1000000000 + ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);

    ret = fd_msg_free(*msg);
    ogs_assert(ret == 0);
    *msg = NULL;

    state_cleanup(sess_data, NULL, NULL);
    return;
}

/* MME received Purge UE Answer from HSS */
static void mme_s6a_pua_cb(void *data, struct msg **msg)
{
    int ret;

    struct sess_state *sess_data = NULL;
    struct timespec ts;
    struct session *session;
    struct avp *avp, *avpch;
    struct avp_hdr *hdr;
    unsigned long dur;
    int error = 0;
    int new;

    mme_event_t *e = NULL;
    mme_ue_t *mme_ue = NULL;
    ogs_diam_s6a_message_t *s6a_message = NULL;
    ogs_diam_s6a_pua_message_t *pua_message = NULL;

    ogs_debug("[MME] Purge-UE-Answer");

    ret = clock_gettime(CLOCK_REALTIME, &ts);
    ogs_assert(ret == 0);

    /* Search the session, retrieve its data */
    ret = fd_msg_sess_get(fd_g_config->cnf_dict, *msg, &session, &new);
    if (ret != 0) {
        ogs_error("fd_msg_sess_get() failed");
        return;
    }
    if (new != 0) {
        ogs_error("fd_msg_sess_get() failed");
        return;
    }

    ret = fd_sess_state_retrieve(mme_s6a_reg, session, &sess_data);
    if (ret != 0) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }
    if (!sess_data) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }
    if ((void *)sess_data != data) {
        ogs_error("fd_sess_state_retrieve() failed");
        return;
    }

    mme_ue = sess_data->mme_ue;
    ogs_assert(mme_ue);

    /* Set Purge-UE Command */
    s6a_message = ogs_calloc(1, sizeof(ogs_diam_s6a_message_t));
    ogs_assert(s6a_message);
    s6a_message->cmd_code = OGS_DIAM_S6A_CMD_CODE_PURGE_UE;
    pua_message = &s6a_message->pua_message;
    ogs_assert(pua_message);

    /* AVP: 'Result-Code'(268)
     * The Result-Code AVP indicates whether a particular request was completed
     * successfully or whether an error occurred. The Result-Code data field
     * contains an IANA-managed 32-bit address space representing errors.
     * Reference: RFC 6733
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_result_code, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        s6a_message->result_code = hdr->avp_value->i32;
        s6a_message->err = &s6a_message->result_code;
        ogs_debug("    Result Code: %d", hdr->avp_value->i32);
    } else {
        ret = fd_msg_search_avp(*msg, ogs_diam_experimental_result, &avp);
        ogs_assert(ret == 0);
        if (avp) {
            ret = fd_avp_search_avp(avp,
                    ogs_diam_experimental_result_code, &avpch);
            ogs_assert(ret == 0);
            if (avpch) {
                ret = fd_msg_avp_hdr(avpch, &hdr);
                ogs_assert(ret == 0);
                s6a_message->result_code = hdr->avp_value->i32;
                s6a_message->exp_err = &s6a_message->result_code;
                ogs_debug("    Experimental Result Code: %d",
                        s6a_message->result_code);
            }
        } else {
            ogs_error("no Result-Code");
            error++;
        }
    }

    /* AVP: 'Origin-Host'(264)
     * The Origin-Host AVP identifies the endpoint that originated the Diameter
     * message. Relay agents MUST NOT modify this AVP. The value of the
     * Origin-Host AVP is guaranteed to be unique within a single host.
     * Reference: RFC 6733
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_origin_host, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        ogs_debug("    From '%.*s'",
                (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
    } else {
        ogs_error("no_Origin-Host");
        error++;
    }

    /* AVP: 'Origin-Realm'(296)
     * This AVP contains the Realm of the originator of any Diameter message
     * and MUST be present in all messages. This AVP SHOULD be placed as close
     * to the Diameter header as possible.
     * Reference: RFC 6733
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_origin_realm, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        ogs_debug("         ('%.*s')",
                (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
    } else {
        ogs_error("no_Origin-Realm");
        error++;
    }

    /* AVP: 'PUA-Flags'(1406)
     * The PUA-Flags AVP contains a bit mask, whose meanings are defined in
     * table in 29.272 7.3.8/1.
     * Reference: 3GPP TS 29.272-f70
     */
    ret = fd_msg_search_avp(*msg, ogs_diam_s6a_pua_flags, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        pua_message->pua_flags = hdr->avp_value->i32;
    }

    if (!error) {
        int rv;
        e = mme_event_new(MME_EVENT_S6A_MESSAGE);
        ogs_assert(e);
        e->mme_ue = mme_ue;
        e->s6a_message = s6a_message;
        rv = ogs_queue_push(ogs_app()->queue, e);
        if (rv != OGS_OK) {
            ogs_error("ogs_queue_push() failed:%d", (int)rv);
            ogs_free(s6a_message);
            mme_event_free(e);
        } else {
            ogs_pollset_notify(ogs_app()->pollset);
        }
    } else {
        ogs_free(s6a_message);
    }

    /* Free the message */
    ogs_assert(pthread_mutex_lock(&ogs_diam_logger_self()->stats_lock) == 0);
    dur = ((ts.tv_sec - sess_data->ts.tv_sec) * 1000000) +
        ((ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);
    if (ogs_diam_logger_self()->stats.nb_recv) {
        /* Ponderate in the avg */
        ogs_diam_logger_self()->stats.avg =
            (ogs_diam_logger_self()->stats.avg *
            ogs_diam_logger_self()->stats.nb_recv + dur) /
            (ogs_diam_logger_self()->stats.nb_recv + 1);
        /* Min, max */
        if (dur < ogs_diam_logger_self()->stats.shortest)
            ogs_diam_logger_self()->stats.shortest = dur;
        if (dur > ogs_diam_logger_self()->stats.longest)
            ogs_diam_logger_self()->stats.longest = dur;
    } else {
        ogs_diam_logger_self()->stats.shortest = dur;
        ogs_diam_logger_self()->stats.longest = dur;
        ogs_diam_logger_self()->stats.avg = dur;
    }
    if (error)
        ogs_diam_logger_self()->stats.nb_errs++;
    else
        ogs_diam_logger_self()->stats.nb_recv++;

    ogs_assert(pthread_mutex_unlock(&ogs_diam_logger_self()->stats_lock) == 0);

    /* Display how long it took */
    if (ts.tv_nsec > sess_data->ts.tv_nsec)
        ogs_trace("in %d.%06ld sec",
                (int)(ts.tv_sec - sess_data->ts.tv_sec),
                (long)(ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);
    else
        ogs_trace("in %d.%06ld sec",
                (int)(ts.tv_sec + 1 - sess_data->ts.tv_sec),
                (long)(1000000000 + ts.tv_nsec - sess_data->ts.tv_nsec) / 1000);

    ret = fd_msg_free(*msg);
    ogs_assert(ret == 0);
    *msg = NULL;

    state_cleanup(sess_data, NULL, NULL);
    return;
}

/* Callback for incoming Cancel-Location-Request messages */
static int mme_ogs_diam_s6a_clr_cb( struct msg **msg, struct avp *avp,
        struct session *session, void *opaque, enum disp_action *act)
{
    int ret, rv;
    
    mme_event_t *e = NULL;
    mme_ue_t *mme_ue = NULL;

    struct msg *ans, *qry;
    ogs_diam_s6a_clr_message_t *clr_message = NULL;    

    struct avp_hdr *hdr;
    union avp_value val;

    char imsi_bcd[OGS_MAX_IMSI_BCD_LEN+1];

    uint32_t result_code = 0;

    ogs_assert(msg);

    ogs_diam_s6a_message_t *s6a_message = NULL;

    ogs_debug("Cancel-Location-Request");

    s6a_message = ogs_calloc(1, sizeof(ogs_diam_s6a_message_t));
    ogs_assert(s6a_message);
    s6a_message->cmd_code = OGS_DIAM_S6A_CMD_CODE_CANCEL_LOCATION;
    clr_message = &s6a_message->clr_message;
    ogs_assert(clr_message);

    /* Create answer header */
    qry = *msg;
    ret = fd_msg_new_answer_from_req(fd_g_config->cnf_dict, msg, 0);
    ogs_assert(ret == 0);
    ans = *msg;

    ret = fd_msg_search_avp(qry, ogs_diam_user_name, &avp);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_hdr(avp, &hdr);
    ogs_assert(ret == 0);

    ogs_cpystrn(imsi_bcd, (char*)hdr->avp_value->os.data,
        ogs_min(hdr->avp_value->os.len, OGS_MAX_IMSI_BCD_LEN)+1);

    mme_ue = mme_ue_find_by_imsi_bcd(imsi_bcd);

    if (!mme_ue) {
        ogs_error("Cancel Location for Unknown IMSI[%s]", imsi_bcd);
        result_code = OGS_DIAM_S6A_ERROR_USER_UNKNOWN;
        goto out;
    }

    ret = fd_msg_search_avp(qry, ogs_diam_s6a_cancellation_type, &avp);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_hdr(avp, &hdr);
    ogs_assert(ret == 0);
    clr_message->cancellation_type = hdr->avp_value->i32;

    /* Set the Origin-Host, Origin-Realm, andResult-Code AVPs */
    ret = fd_msg_rescode_set(ans, (char*)"DIAMETER_SUCCESS", NULL, NULL, 1);
    ogs_assert(ret == 0);

    /* Set the Auth-Session-State AVP */
    ret = fd_msg_avp_new(ogs_diam_auth_session_state, 0, &avp);
    ogs_assert(ret == 0);
    val.i32 = OGS_DIAM_AUTH_SESSION_NO_STATE_MAINTAINED;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(ans, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    ret = fd_msg_search_avp(qry, ogs_diam_s6a_clr_flags, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        clr_message->clr_flags = hdr->avp_value->i32;
    }

    /* Set Vendor-Specific-Application-Id AVP */
    ret = ogs_diam_message_vendor_specific_appid_set(
            ans, OGS_DIAM_S6A_APPLICATION_ID);
    ogs_assert(ret == 0);

    /* Send the answer */
    ret = fd_msg_send(msg, NULL, NULL);
    ogs_assert(ret == 0);

    ogs_debug("Cancel-Location-Answer");

    /* Add this value to the stats */
    ogs_assert( pthread_mutex_lock(&ogs_diam_logger_self()->stats_lock) == 0);
    ogs_diam_logger_self()->stats.nb_echoed++;
    ogs_assert( pthread_mutex_unlock(&ogs_diam_logger_self()->stats_lock) == 0);

    e = mme_event_new(MME_EVENT_S6A_MESSAGE);
    ogs_assert(e);
    e->mme_ue = mme_ue;
    e->s6a_message = s6a_message;
    rv = ogs_queue_push(ogs_app()->queue, e);
    if (rv != OGS_OK) {
        ogs_error("ogs_queue_push() failed:%d", (int)rv);
        ogs_free(s6a_message);
        mme_event_free(e);
    } else {
        ogs_pollset_notify(ogs_app()->pollset);
    }

    return 0;

out:
    ret = ogs_diam_message_experimental_rescode_set(ans, result_code);
    ogs_assert(ret == 0);

    /* Set the Auth-Session-State AVP */
    ret = fd_msg_avp_new(ogs_diam_auth_session_state, 0, &avp);
    ogs_assert(ret == 0);
    val.i32 = OGS_DIAM_AUTH_SESSION_NO_STATE_MAINTAINED;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(ans, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);
    
    /* Set Vendor-Specific-Application-Id AVP */
    ret = ogs_diam_message_vendor_specific_appid_set(
            ans, OGS_DIAM_S6A_APPLICATION_ID);
    ogs_assert(ret == 0);

    /* Send the answer */
    ret = fd_msg_send(msg, NULL, NULL);
    ogs_assert(ret == 0);

    ogs_free(s6a_message);

    return 0;
}

/* Callback for incoming Insert-Subscriber-Data-Request messages
 * 29.272 5.2.2.1.2 */
static int mme_ogs_diam_s6a_idr_cb( struct msg **msg, struct avp *avp,
        struct session *session, void *opaque, enum disp_action *act)
{
    int ret;
    char imsi_bcd[OGS_MAX_IMSI_BCD_LEN+1];
    uint32_t result_code = 0;
    bool has_subscriber_data;
    
    struct msg *ans, *qry;

    mme_event_t *e = NULL;
    mme_ue_t *mme_ue = NULL;
    ogs_diam_s6a_message_t *s6a_message = NULL;
    ogs_diam_s6a_idr_message_t *idr_message = NULL;
    ogs_subscription_data_t *subscription_data = NULL;

    struct avp_hdr *hdr;
    union avp_value val;

    ogs_assert(msg);

    ogs_debug("Insert-Subscriber-Data-Request");

    s6a_message = ogs_calloc(1, sizeof(ogs_diam_s6a_message_t));
    ogs_assert(s6a_message);
    s6a_message->cmd_code = OGS_DIAM_S6A_CMD_CODE_INSERT_SUBSCRIBER_DATA;
    idr_message = &s6a_message->idr_message;
    ogs_assert(idr_message);
    subscription_data = &idr_message->subscription_data;
    ogs_assert(subscription_data);

    /* Create answer header */
    qry = *msg;
    ret = fd_msg_new_answer_from_req(fd_g_config->cnf_dict, msg, 0);
    ogs_assert(ret == 0);
    ans = *msg;

    ret = fd_msg_search_avp(qry, ogs_diam_user_name, &avp);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_hdr(avp, &hdr);
    ogs_assert(ret == 0);

    ogs_cpystrn(imsi_bcd, (char*)hdr->avp_value->os.data,
        ogs_min(hdr->avp_value->os.len, OGS_MAX_IMSI_BCD_LEN)+1);

    mme_ue = mme_ue_find_by_imsi_bcd(imsi_bcd);

    if (!mme_ue) {
        ogs_error("Insert Subscriber Data for Unknown IMSI[%s]", imsi_bcd);
        result_code = OGS_DIAM_S6A_ERROR_USER_UNKNOWN;
        goto out;
    }

    /* AVP: 'Subscription-Data'(1400)
     * The Subscription-Data AVP contains the information related to the user
     * profile relevant for EPS and GERAN/UTRAN.
     * Reference: 3GPP TS 29.272-f70
     */
    ret = fd_msg_search_avp(qry, ogs_diam_s6a_subscription_data, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        ret = fd_msg_browse(avp, MSG_BRW_FIRST_CHILD, NULL, NULL);
        if (ret) {
            ogs_info("[%s] Subscription-Data is Empty.", imsi_bcd);
        } else {
            has_subscriber_data = true;
            uint32_t subdatamask = 0;
            ret = mme_s6a_subscription_data_from_avp(avp, subscription_data, 
                mme_ue, &subdatamask);
            idr_message->subdatamask = subdatamask;
            ogs_info("[%s] Subscription-Data Processed.", imsi_bcd);
        }
    }

    ret = fd_msg_search_avp(qry, ogs_diam_s6a_idr_flags, &avp);
    ogs_assert(ret == 0);
    if (avp) {
        ret = fd_msg_avp_hdr(avp, &hdr);
        ogs_assert(ret == 0);
        idr_message->idr_flags = hdr->avp_value->i32;
    }

    if (idr_message->idr_flags & OGS_DIAM_S6A_IDR_FLAGS_EPS_LOCATION_INFO) {
        char buf[8];

        uint8_t ida_ecgi[8];
        uint8_t ida_tai[5];
        ogs_time_t ida_age;

        ogs_nas_plmn_id_t ida_plmn_buf;
        char ida_cell_id_hex[9];
        char ida_tac_hex[5];

        uint32_t ida_cell_id = mme_ue->e_cgi.cell_id;
        uint16_t ida_tac = mme_ue->tai.tac;
        
        struct avp *avp_mme_location_information;
        struct avp *avp_e_utran_cell_global_identity;
        struct avp *avp_tracking_area_identity;
        struct avp *avp_age_of_location_information;

        ogs_snprintf(ida_cell_id_hex, sizeof(ida_cell_id_hex),
                "%08x", ida_cell_id);
        memcpy(ida_ecgi,
                ogs_nas_from_plmn_id(&ida_plmn_buf, &mme_ue->e_cgi.plmn_id), 3);
        memcpy(ida_ecgi + 3,
                ogs_hex_from_string(ida_cell_id_hex, buf, sizeof(buf)), 5);

        ogs_snprintf(ida_tac_hex, sizeof(ida_tac_hex), "%04x", ida_tac);
        memcpy(ida_tai,
                ogs_nas_from_plmn_id(&ida_plmn_buf, &mme_ue->tai.plmn_id), 3);
        memcpy(ida_tai + 3,
                ogs_hex_from_string(ida_tac_hex, buf, sizeof(buf)), 2);

        ida_age =
            (ogs_time_now() - mme_ue->ue_location_timestamp) / 1000000 / 60;

        /* Set the EPS-Location-Information AVP */
        ret = fd_msg_avp_new(ogs_diam_s6a_eps_location_information, 0, &avp);
        ogs_assert(ret == 0);
        ret = fd_msg_avp_new(ogs_diam_s6a_mme_location_information,
                0, &avp_mme_location_information);
        ogs_assert(ret == 0);

        ret = fd_msg_avp_new(ogs_diam_s6a_e_utran_cell_global_identity,
                0, &avp_e_utran_cell_global_identity);
        ogs_assert(ret == 0);
        val.os.data = ida_ecgi;
        val.os.len  = 7;
        ret = fd_msg_avp_setvalue(avp_e_utran_cell_global_identity, &val);
        ogs_assert(ret == 0);
        ret = fd_msg_avp_add(avp_mme_location_information,
                MSG_BRW_LAST_CHILD, avp_e_utran_cell_global_identity);
        ogs_assert(ret == 0);

        ret = fd_msg_avp_new(ogs_diam_s6a_tracking_area_identity,
                0, &avp_tracking_area_identity);
        ogs_assert(ret == 0);
        val.os.data = ida_tai;
        val.os.len  = 5;
        ret = fd_msg_avp_setvalue(avp_tracking_area_identity, &val);
        ogs_assert(ret == 0);
        ret = fd_msg_avp_add(avp_mme_location_information,
                MSG_BRW_LAST_CHILD, avp_tracking_area_identity);
        ogs_assert(ret == 0);

        ret = fd_msg_avp_new(ogs_diam_s6a_age_of_location_information,
                0, &avp_age_of_location_information);
        ogs_assert(ret == 0);
        val.i32 = ida_age;
        ret = fd_msg_avp_setvalue(avp_age_of_location_information, &val);
        ogs_assert(ret == 0);
        ret = fd_msg_avp_add(avp_mme_location_information,
                MSG_BRW_LAST_CHILD, avp_age_of_location_information);
        ogs_assert(ret == 0);

        ret = fd_msg_avp_add(avp,
                MSG_BRW_LAST_CHILD, avp_mme_location_information);
        ogs_assert(ret == 0);

        ret = fd_msg_avp_add(ans, MSG_BRW_LAST_CHILD, avp);
        ogs_assert(ret == 0);        
    } else {
        if (!has_subscriber_data) {
            ogs_error("Insert Subscriber Data "
                    "with unsupported IDR Flags "
                    "or no Subscriber-Data for IMSI[%s]", imsi_bcd);
            /* Set the Origin-Host, Origin-Realm, and Result-Code AVPs */
            ret = fd_msg_rescode_set(
                    ans, (char*)"DIAMETER_UNABLE_TO_COMPLY", NULL, NULL, 1);
            ogs_assert(ret == 0);
            goto outnoexp;
        }
    }

    /* Set the Origin-Host, Origin-Realm, andResult-Code AVPs */
    ret = fd_msg_rescode_set(ans, (char*)"DIAMETER_SUCCESS", NULL, NULL, 1);
    ogs_assert(ret == 0);

    /* Set the Auth-Session-State AVP */
    ret = fd_msg_avp_new(ogs_diam_auth_session_state, 0, &avp);
    ogs_assert(ret == 0);
    val.i32 = OGS_DIAM_AUTH_SESSION_NO_STATE_MAINTAINED;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(ans, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);

    /* Set Vendor-Specific-Application-Id AVP */
    ret = ogs_diam_message_vendor_specific_appid_set(
            ans, OGS_DIAM_S6A_APPLICATION_ID);
    ogs_assert(ret == 0);

    /* Send the answer */
    ret = fd_msg_send(msg, NULL, NULL);
    ogs_assert(ret == 0);

    ogs_debug("Insert-Subscriber-Data-Answer");

    /* Add this value to the stats */
    ogs_assert( pthread_mutex_lock(&ogs_diam_logger_self()->stats_lock) == 0);
    ogs_diam_logger_self()->stats.nb_echoed++;
    ogs_assert( pthread_mutex_unlock(&ogs_diam_logger_self()->stats_lock) == 0);

    int rv;
    e = mme_event_new(MME_EVENT_S6A_MESSAGE);
    ogs_assert(e);
    e->mme_ue = mme_ue;
    e->s6a_message = s6a_message;
    rv = ogs_queue_push(ogs_app()->queue, e);
    if (rv != OGS_OK) {
        ogs_error("ogs_queue_push() failed:%d", (int)rv);
        ogs_subscription_data_free(subscription_data);
        ogs_free(s6a_message);
        mme_event_free(e);
    } else {
        ogs_pollset_notify(ogs_app()->pollset);
    }

    return 0;

out:
    ret = ogs_diam_message_experimental_rescode_set(ans, result_code);
    ogs_assert(ret == 0);
outnoexp:
    /* Set the Auth-Session-State AVP */
    ret = fd_msg_avp_new(ogs_diam_auth_session_state, 0, &avp);
    ogs_assert(ret == 0);
    val.i32 = OGS_DIAM_AUTH_SESSION_NO_STATE_MAINTAINED;
    ret = fd_msg_avp_setvalue(avp, &val);
    ogs_assert(ret == 0);
    ret = fd_msg_avp_add(ans, MSG_BRW_LAST_CHILD, avp);
    ogs_assert(ret == 0);
    
    /* Set Vendor-Specific-Application-Id AVP */
    ret = ogs_diam_message_vendor_specific_appid_set(
            ans, OGS_DIAM_S6A_APPLICATION_ID);
    ogs_assert(ret == 0);

    /* Send the answer */
    ret = fd_msg_send(msg, NULL, NULL);
    ogs_assert(ret == 0);

    ogs_free(s6a_message);

    return 0;
}

int mme_fd_init(void)
{
    int ret;
    struct disp_when data;

    ret = ogs_diam_init(FD_MODE_CLIENT,
                mme_self()->diam_conf_path, mme_self()->diam_config);
    ogs_assert(ret == 0);

    /* Install objects definitions for this application */
    ret = ogs_diam_s6a_init();
    ogs_assert(ret == OGS_OK);

    /* Create handler for sessions */
    ret = fd_sess_handler_create(&mme_s6a_reg, &state_cleanup, NULL, NULL);
    ogs_assert(ret == 0);

    /* Specific handler for Cancel-Location-Request */
    memset(&data, 0, sizeof(data));
    data.command = ogs_diam_s6a_cmd_clr;
    ret = fd_disp_register(mme_ogs_diam_s6a_clr_cb, DISP_HOW_CC, &data, NULL,
                &hdl_s6a_clr);
    ogs_assert(ret == 0);

    /* Specific handler for Insert-Subscriber-Data-Request */
    data.command = ogs_diam_s6a_cmd_idr;
    ret = fd_disp_register(mme_ogs_diam_s6a_idr_cb, DISP_HOW_CC, &data, NULL,
                &hdl_s6a_idr);
    ogs_assert(ret == 0);    

    /* Advertise the support for the application in the peer */
    ret = fd_disp_app_support(ogs_diam_s6a_application, ogs_diam_vendor, 1, 0);
    ogs_assert(ret == 0);

    ret = ogs_diam_start();
    ogs_assert(ret == 0);

    return 0;
}

void mme_fd_final(void)
{
    int ret;

    ret = fd_sess_handler_destroy(&mme_s6a_reg, NULL);
    ogs_assert(ret == OGS_OK);

    if (hdl_s6a_clr)
        (void) fd_disp_unregister(&hdl_s6a_clr, NULL);

    if (hdl_s6a_idr)
        (void) fd_disp_unregister(&hdl_s6a_idr, NULL);

    ogs_diam_final();
}
