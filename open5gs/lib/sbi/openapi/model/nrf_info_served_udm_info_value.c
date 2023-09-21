
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nrf_info_served_udm_info_value.h"

OpenAPI_nrf_info_served_udm_info_value_t *OpenAPI_nrf_info_served_udm_info_value_create(
    char *group_id,
    OpenAPI_list_t *supi_ranges,
    OpenAPI_list_t *gpsi_ranges,
    OpenAPI_list_t *external_group_identifiers_ranges,
    OpenAPI_list_t *routing_indicators,
    OpenAPI_list_t *internal_group_identifiers_ranges,
    OpenAPI_list_t *suci_infos
)
{
    OpenAPI_nrf_info_served_udm_info_value_t *nrf_info_served_udm_info_value_local_var = ogs_malloc(sizeof(OpenAPI_nrf_info_served_udm_info_value_t));
    ogs_assert(nrf_info_served_udm_info_value_local_var);

    nrf_info_served_udm_info_value_local_var->group_id = group_id;
    nrf_info_served_udm_info_value_local_var->supi_ranges = supi_ranges;
    nrf_info_served_udm_info_value_local_var->gpsi_ranges = gpsi_ranges;
    nrf_info_served_udm_info_value_local_var->external_group_identifiers_ranges = external_group_identifiers_ranges;
    nrf_info_served_udm_info_value_local_var->routing_indicators = routing_indicators;
    nrf_info_served_udm_info_value_local_var->internal_group_identifiers_ranges = internal_group_identifiers_ranges;
    nrf_info_served_udm_info_value_local_var->suci_infos = suci_infos;

    return nrf_info_served_udm_info_value_local_var;
}

void OpenAPI_nrf_info_served_udm_info_value_free(OpenAPI_nrf_info_served_udm_info_value_t *nrf_info_served_udm_info_value)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == nrf_info_served_udm_info_value) {
        return;
    }
    if (nrf_info_served_udm_info_value->group_id) {
        ogs_free(nrf_info_served_udm_info_value->group_id);
        nrf_info_served_udm_info_value->group_id = NULL;
    }
    if (nrf_info_served_udm_info_value->supi_ranges) {
        OpenAPI_list_for_each(nrf_info_served_udm_info_value->supi_ranges, node) {
            OpenAPI_supi_range_free(node->data);
        }
        OpenAPI_list_free(nrf_info_served_udm_info_value->supi_ranges);
        nrf_info_served_udm_info_value->supi_ranges = NULL;
    }
    if (nrf_info_served_udm_info_value->gpsi_ranges) {
        OpenAPI_list_for_each(nrf_info_served_udm_info_value->gpsi_ranges, node) {
            OpenAPI_identity_range_free(node->data);
        }
        OpenAPI_list_free(nrf_info_served_udm_info_value->gpsi_ranges);
        nrf_info_served_udm_info_value->gpsi_ranges = NULL;
    }
    if (nrf_info_served_udm_info_value->external_group_identifiers_ranges) {
        OpenAPI_list_for_each(nrf_info_served_udm_info_value->external_group_identifiers_ranges, node) {
            OpenAPI_identity_range_free(node->data);
        }
        OpenAPI_list_free(nrf_info_served_udm_info_value->external_group_identifiers_ranges);
        nrf_info_served_udm_info_value->external_group_identifiers_ranges = NULL;
    }
    if (nrf_info_served_udm_info_value->routing_indicators) {
        OpenAPI_list_for_each(nrf_info_served_udm_info_value->routing_indicators, node) {
            ogs_free(node->data);
        }
        OpenAPI_list_free(nrf_info_served_udm_info_value->routing_indicators);
        nrf_info_served_udm_info_value->routing_indicators = NULL;
    }
    if (nrf_info_served_udm_info_value->internal_group_identifiers_ranges) {
        OpenAPI_list_for_each(nrf_info_served_udm_info_value->internal_group_identifiers_ranges, node) {
            OpenAPI_internal_group_id_range_free(node->data);
        }
        OpenAPI_list_free(nrf_info_served_udm_info_value->internal_group_identifiers_ranges);
        nrf_info_served_udm_info_value->internal_group_identifiers_ranges = NULL;
    }
    if (nrf_info_served_udm_info_value->suci_infos) {
        OpenAPI_list_for_each(nrf_info_served_udm_info_value->suci_infos, node) {
            OpenAPI_suci_info_free(node->data);
        }
        OpenAPI_list_free(nrf_info_served_udm_info_value->suci_infos);
        nrf_info_served_udm_info_value->suci_infos = NULL;
    }
    ogs_free(nrf_info_served_udm_info_value);
}

cJSON *OpenAPI_nrf_info_served_udm_info_value_convertToJSON(OpenAPI_nrf_info_served_udm_info_value_t *nrf_info_served_udm_info_value)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (nrf_info_served_udm_info_value == NULL) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [NrfInfo_servedUdmInfo_value]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (nrf_info_served_udm_info_value->group_id) {
    if (cJSON_AddStringToObject(item, "groupId", nrf_info_served_udm_info_value->group_id) == NULL) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [group_id]");
        goto end;
    }
    }

    if (nrf_info_served_udm_info_value->supi_ranges) {
    cJSON *supi_rangesList = cJSON_AddArrayToObject(item, "supiRanges");
    if (supi_rangesList == NULL) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [supi_ranges]");
        goto end;
    }
    OpenAPI_list_for_each(nrf_info_served_udm_info_value->supi_ranges, node) {
        cJSON *itemLocal = OpenAPI_supi_range_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [supi_ranges]");
            goto end;
        }
        cJSON_AddItemToArray(supi_rangesList, itemLocal);
    }
    }

    if (nrf_info_served_udm_info_value->gpsi_ranges) {
    cJSON *gpsi_rangesList = cJSON_AddArrayToObject(item, "gpsiRanges");
    if (gpsi_rangesList == NULL) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [gpsi_ranges]");
        goto end;
    }
    OpenAPI_list_for_each(nrf_info_served_udm_info_value->gpsi_ranges, node) {
        cJSON *itemLocal = OpenAPI_identity_range_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [gpsi_ranges]");
            goto end;
        }
        cJSON_AddItemToArray(gpsi_rangesList, itemLocal);
    }
    }

    if (nrf_info_served_udm_info_value->external_group_identifiers_ranges) {
    cJSON *external_group_identifiers_rangesList = cJSON_AddArrayToObject(item, "externalGroupIdentifiersRanges");
    if (external_group_identifiers_rangesList == NULL) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [external_group_identifiers_ranges]");
        goto end;
    }
    OpenAPI_list_for_each(nrf_info_served_udm_info_value->external_group_identifiers_ranges, node) {
        cJSON *itemLocal = OpenAPI_identity_range_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [external_group_identifiers_ranges]");
            goto end;
        }
        cJSON_AddItemToArray(external_group_identifiers_rangesList, itemLocal);
    }
    }

    if (nrf_info_served_udm_info_value->routing_indicators) {
    cJSON *routing_indicatorsList = cJSON_AddArrayToObject(item, "routingIndicators");
    if (routing_indicatorsList == NULL) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [routing_indicators]");
        goto end;
    }
    OpenAPI_list_for_each(nrf_info_served_udm_info_value->routing_indicators, node) {
        if (cJSON_AddStringToObject(routing_indicatorsList, "", (char*)node->data) == NULL) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [routing_indicators]");
            goto end;
        }
    }
    }

    if (nrf_info_served_udm_info_value->internal_group_identifiers_ranges) {
    cJSON *internal_group_identifiers_rangesList = cJSON_AddArrayToObject(item, "internalGroupIdentifiersRanges");
    if (internal_group_identifiers_rangesList == NULL) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [internal_group_identifiers_ranges]");
        goto end;
    }
    OpenAPI_list_for_each(nrf_info_served_udm_info_value->internal_group_identifiers_ranges, node) {
        cJSON *itemLocal = OpenAPI_internal_group_id_range_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [internal_group_identifiers_ranges]");
            goto end;
        }
        cJSON_AddItemToArray(internal_group_identifiers_rangesList, itemLocal);
    }
    }

    if (nrf_info_served_udm_info_value->suci_infos) {
    cJSON *suci_infosList = cJSON_AddArrayToObject(item, "suciInfos");
    if (suci_infosList == NULL) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [suci_infos]");
        goto end;
    }
    OpenAPI_list_for_each(nrf_info_served_udm_info_value->suci_infos, node) {
        cJSON *itemLocal = OpenAPI_suci_info_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed [suci_infos]");
            goto end;
        }
        cJSON_AddItemToArray(suci_infosList, itemLocal);
    }
    }

end:
    return item;
}

OpenAPI_nrf_info_served_udm_info_value_t *OpenAPI_nrf_info_served_udm_info_value_parseFromJSON(cJSON *nrf_info_served_udm_info_valueJSON)
{
    OpenAPI_nrf_info_served_udm_info_value_t *nrf_info_served_udm_info_value_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *group_id = NULL;
    cJSON *supi_ranges = NULL;
    OpenAPI_list_t *supi_rangesList = NULL;
    cJSON *gpsi_ranges = NULL;
    OpenAPI_list_t *gpsi_rangesList = NULL;
    cJSON *external_group_identifiers_ranges = NULL;
    OpenAPI_list_t *external_group_identifiers_rangesList = NULL;
    cJSON *routing_indicators = NULL;
    OpenAPI_list_t *routing_indicatorsList = NULL;
    cJSON *internal_group_identifiers_ranges = NULL;
    OpenAPI_list_t *internal_group_identifiers_rangesList = NULL;
    cJSON *suci_infos = NULL;
    OpenAPI_list_t *suci_infosList = NULL;
    group_id = cJSON_GetObjectItemCaseSensitive(nrf_info_served_udm_info_valueJSON, "groupId");
    if (group_id) {
    if (!cJSON_IsString(group_id) && !cJSON_IsNull(group_id)) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [group_id]");
        goto end;
    }
    }

    supi_ranges = cJSON_GetObjectItemCaseSensitive(nrf_info_served_udm_info_valueJSON, "supiRanges");
    if (supi_ranges) {
        cJSON *supi_ranges_local = NULL;
        if (!cJSON_IsArray(supi_ranges)) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [supi_ranges]");
            goto end;
        }

        supi_rangesList = OpenAPI_list_create();

        cJSON_ArrayForEach(supi_ranges_local, supi_ranges) {
            if (!cJSON_IsObject(supi_ranges_local)) {
                ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [supi_ranges]");
                goto end;
            }
            OpenAPI_supi_range_t *supi_rangesItem = OpenAPI_supi_range_parseFromJSON(supi_ranges_local);
            if (!supi_rangesItem) {
                ogs_error("No supi_rangesItem");
                goto end;
            }
            OpenAPI_list_add(supi_rangesList, supi_rangesItem);
        }
    }

    gpsi_ranges = cJSON_GetObjectItemCaseSensitive(nrf_info_served_udm_info_valueJSON, "gpsiRanges");
    if (gpsi_ranges) {
        cJSON *gpsi_ranges_local = NULL;
        if (!cJSON_IsArray(gpsi_ranges)) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [gpsi_ranges]");
            goto end;
        }

        gpsi_rangesList = OpenAPI_list_create();

        cJSON_ArrayForEach(gpsi_ranges_local, gpsi_ranges) {
            if (!cJSON_IsObject(gpsi_ranges_local)) {
                ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [gpsi_ranges]");
                goto end;
            }
            OpenAPI_identity_range_t *gpsi_rangesItem = OpenAPI_identity_range_parseFromJSON(gpsi_ranges_local);
            if (!gpsi_rangesItem) {
                ogs_error("No gpsi_rangesItem");
                goto end;
            }
            OpenAPI_list_add(gpsi_rangesList, gpsi_rangesItem);
        }
    }

    external_group_identifiers_ranges = cJSON_GetObjectItemCaseSensitive(nrf_info_served_udm_info_valueJSON, "externalGroupIdentifiersRanges");
    if (external_group_identifiers_ranges) {
        cJSON *external_group_identifiers_ranges_local = NULL;
        if (!cJSON_IsArray(external_group_identifiers_ranges)) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [external_group_identifiers_ranges]");
            goto end;
        }

        external_group_identifiers_rangesList = OpenAPI_list_create();

        cJSON_ArrayForEach(external_group_identifiers_ranges_local, external_group_identifiers_ranges) {
            if (!cJSON_IsObject(external_group_identifiers_ranges_local)) {
                ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [external_group_identifiers_ranges]");
                goto end;
            }
            OpenAPI_identity_range_t *external_group_identifiers_rangesItem = OpenAPI_identity_range_parseFromJSON(external_group_identifiers_ranges_local);
            if (!external_group_identifiers_rangesItem) {
                ogs_error("No external_group_identifiers_rangesItem");
                goto end;
            }
            OpenAPI_list_add(external_group_identifiers_rangesList, external_group_identifiers_rangesItem);
        }
    }

    routing_indicators = cJSON_GetObjectItemCaseSensitive(nrf_info_served_udm_info_valueJSON, "routingIndicators");
    if (routing_indicators) {
        cJSON *routing_indicators_local = NULL;
        if (!cJSON_IsArray(routing_indicators)) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [routing_indicators]");
            goto end;
        }

        routing_indicatorsList = OpenAPI_list_create();

        cJSON_ArrayForEach(routing_indicators_local, routing_indicators) {
            double *localDouble = NULL;
            int *localInt = NULL;
            if (!cJSON_IsString(routing_indicators_local)) {
                ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [routing_indicators]");
                goto end;
            }
            OpenAPI_list_add(routing_indicatorsList, ogs_strdup(routing_indicators_local->valuestring));
        }
    }

    internal_group_identifiers_ranges = cJSON_GetObjectItemCaseSensitive(nrf_info_served_udm_info_valueJSON, "internalGroupIdentifiersRanges");
    if (internal_group_identifiers_ranges) {
        cJSON *internal_group_identifiers_ranges_local = NULL;
        if (!cJSON_IsArray(internal_group_identifiers_ranges)) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [internal_group_identifiers_ranges]");
            goto end;
        }

        internal_group_identifiers_rangesList = OpenAPI_list_create();

        cJSON_ArrayForEach(internal_group_identifiers_ranges_local, internal_group_identifiers_ranges) {
            if (!cJSON_IsObject(internal_group_identifiers_ranges_local)) {
                ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [internal_group_identifiers_ranges]");
                goto end;
            }
            OpenAPI_internal_group_id_range_t *internal_group_identifiers_rangesItem = OpenAPI_internal_group_id_range_parseFromJSON(internal_group_identifiers_ranges_local);
            if (!internal_group_identifiers_rangesItem) {
                ogs_error("No internal_group_identifiers_rangesItem");
                goto end;
            }
            OpenAPI_list_add(internal_group_identifiers_rangesList, internal_group_identifiers_rangesItem);
        }
    }

    suci_infos = cJSON_GetObjectItemCaseSensitive(nrf_info_served_udm_info_valueJSON, "suciInfos");
    if (suci_infos) {
        cJSON *suci_infos_local = NULL;
        if (!cJSON_IsArray(suci_infos)) {
            ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [suci_infos]");
            goto end;
        }

        suci_infosList = OpenAPI_list_create();

        cJSON_ArrayForEach(suci_infos_local, suci_infos) {
            if (!cJSON_IsObject(suci_infos_local)) {
                ogs_error("OpenAPI_nrf_info_served_udm_info_value_parseFromJSON() failed [suci_infos]");
                goto end;
            }
            OpenAPI_suci_info_t *suci_infosItem = OpenAPI_suci_info_parseFromJSON(suci_infos_local);
            if (!suci_infosItem) {
                ogs_error("No suci_infosItem");
                goto end;
            }
            OpenAPI_list_add(suci_infosList, suci_infosItem);
        }
    }

    nrf_info_served_udm_info_value_local_var = OpenAPI_nrf_info_served_udm_info_value_create (
        group_id && !cJSON_IsNull(group_id) ? ogs_strdup(group_id->valuestring) : NULL,
        supi_ranges ? supi_rangesList : NULL,
        gpsi_ranges ? gpsi_rangesList : NULL,
        external_group_identifiers_ranges ? external_group_identifiers_rangesList : NULL,
        routing_indicators ? routing_indicatorsList : NULL,
        internal_group_identifiers_ranges ? internal_group_identifiers_rangesList : NULL,
        suci_infos ? suci_infosList : NULL
    );

    return nrf_info_served_udm_info_value_local_var;
end:
    if (supi_rangesList) {
        OpenAPI_list_for_each(supi_rangesList, node) {
            OpenAPI_supi_range_free(node->data);
        }
        OpenAPI_list_free(supi_rangesList);
        supi_rangesList = NULL;
    }
    if (gpsi_rangesList) {
        OpenAPI_list_for_each(gpsi_rangesList, node) {
            OpenAPI_identity_range_free(node->data);
        }
        OpenAPI_list_free(gpsi_rangesList);
        gpsi_rangesList = NULL;
    }
    if (external_group_identifiers_rangesList) {
        OpenAPI_list_for_each(external_group_identifiers_rangesList, node) {
            OpenAPI_identity_range_free(node->data);
        }
        OpenAPI_list_free(external_group_identifiers_rangesList);
        external_group_identifiers_rangesList = NULL;
    }
    if (routing_indicatorsList) {
        OpenAPI_list_for_each(routing_indicatorsList, node) {
            ogs_free(node->data);
        }
        OpenAPI_list_free(routing_indicatorsList);
        routing_indicatorsList = NULL;
    }
    if (internal_group_identifiers_rangesList) {
        OpenAPI_list_for_each(internal_group_identifiers_rangesList, node) {
            OpenAPI_internal_group_id_range_free(node->data);
        }
        OpenAPI_list_free(internal_group_identifiers_rangesList);
        internal_group_identifiers_rangesList = NULL;
    }
    if (suci_infosList) {
        OpenAPI_list_for_each(suci_infosList, node) {
            OpenAPI_suci_info_free(node->data);
        }
        OpenAPI_list_free(suci_infosList);
        suci_infosList = NULL;
    }
    return NULL;
}

OpenAPI_nrf_info_served_udm_info_value_t *OpenAPI_nrf_info_served_udm_info_value_copy(OpenAPI_nrf_info_served_udm_info_value_t *dst, OpenAPI_nrf_info_served_udm_info_value_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_nrf_info_served_udm_info_value_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_nrf_info_served_udm_info_value_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_nrf_info_served_udm_info_value_free(dst);
    dst = OpenAPI_nrf_info_served_udm_info_value_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

