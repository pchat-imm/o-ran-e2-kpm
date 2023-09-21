
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "expected_ue_behaviour_data_1.h"

OpenAPI_expected_ue_behaviour_data_1_t *OpenAPI_expected_ue_behaviour_data_1_create(
    OpenAPI_stationary_indication_e stationary_indication,
    bool is_communication_duration_time,
    int communication_duration_time,
    bool is_periodic_time,
    int periodic_time,
    OpenAPI_scheduled_communication_time_1_t *scheduled_communication_time,
    OpenAPI_scheduled_communication_type_e scheduled_communication_type,
    OpenAPI_list_t *expected_umts,
    OpenAPI_traffic_profile_e traffic_profile,
    OpenAPI_battery_indication_t *battery_indication,
    char *validity_time
)
{
    OpenAPI_expected_ue_behaviour_data_1_t *expected_ue_behaviour_data_1_local_var = ogs_malloc(sizeof(OpenAPI_expected_ue_behaviour_data_1_t));
    ogs_assert(expected_ue_behaviour_data_1_local_var);

    expected_ue_behaviour_data_1_local_var->stationary_indication = stationary_indication;
    expected_ue_behaviour_data_1_local_var->is_communication_duration_time = is_communication_duration_time;
    expected_ue_behaviour_data_1_local_var->communication_duration_time = communication_duration_time;
    expected_ue_behaviour_data_1_local_var->is_periodic_time = is_periodic_time;
    expected_ue_behaviour_data_1_local_var->periodic_time = periodic_time;
    expected_ue_behaviour_data_1_local_var->scheduled_communication_time = scheduled_communication_time;
    expected_ue_behaviour_data_1_local_var->scheduled_communication_type = scheduled_communication_type;
    expected_ue_behaviour_data_1_local_var->expected_umts = expected_umts;
    expected_ue_behaviour_data_1_local_var->traffic_profile = traffic_profile;
    expected_ue_behaviour_data_1_local_var->battery_indication = battery_indication;
    expected_ue_behaviour_data_1_local_var->validity_time = validity_time;

    return expected_ue_behaviour_data_1_local_var;
}

void OpenAPI_expected_ue_behaviour_data_1_free(OpenAPI_expected_ue_behaviour_data_1_t *expected_ue_behaviour_data_1)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == expected_ue_behaviour_data_1) {
        return;
    }
    if (expected_ue_behaviour_data_1->scheduled_communication_time) {
        OpenAPI_scheduled_communication_time_1_free(expected_ue_behaviour_data_1->scheduled_communication_time);
        expected_ue_behaviour_data_1->scheduled_communication_time = NULL;
    }
    if (expected_ue_behaviour_data_1->expected_umts) {
        OpenAPI_list_for_each(expected_ue_behaviour_data_1->expected_umts, node) {
            OpenAPI_location_area_1_free(node->data);
        }
        OpenAPI_list_free(expected_ue_behaviour_data_1->expected_umts);
        expected_ue_behaviour_data_1->expected_umts = NULL;
    }
    if (expected_ue_behaviour_data_1->battery_indication) {
        OpenAPI_battery_indication_free(expected_ue_behaviour_data_1->battery_indication);
        expected_ue_behaviour_data_1->battery_indication = NULL;
    }
    if (expected_ue_behaviour_data_1->validity_time) {
        ogs_free(expected_ue_behaviour_data_1->validity_time);
        expected_ue_behaviour_data_1->validity_time = NULL;
    }
    ogs_free(expected_ue_behaviour_data_1);
}

cJSON *OpenAPI_expected_ue_behaviour_data_1_convertToJSON(OpenAPI_expected_ue_behaviour_data_1_t *expected_ue_behaviour_data_1)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (expected_ue_behaviour_data_1 == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [ExpectedUeBehaviourData_1]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (expected_ue_behaviour_data_1->stationary_indication != OpenAPI_stationary_indication_NULL) {
    if (cJSON_AddStringToObject(item, "stationaryIndication", OpenAPI_stationary_indication_ToString(expected_ue_behaviour_data_1->stationary_indication)) == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [stationary_indication]");
        goto end;
    }
    }

    if (expected_ue_behaviour_data_1->is_communication_duration_time) {
    if (cJSON_AddNumberToObject(item, "communicationDurationTime", expected_ue_behaviour_data_1->communication_duration_time) == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [communication_duration_time]");
        goto end;
    }
    }

    if (expected_ue_behaviour_data_1->is_periodic_time) {
    if (cJSON_AddNumberToObject(item, "periodicTime", expected_ue_behaviour_data_1->periodic_time) == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [periodic_time]");
        goto end;
    }
    }

    if (expected_ue_behaviour_data_1->scheduled_communication_time) {
    cJSON *scheduled_communication_time_local_JSON = OpenAPI_scheduled_communication_time_1_convertToJSON(expected_ue_behaviour_data_1->scheduled_communication_time);
    if (scheduled_communication_time_local_JSON == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [scheduled_communication_time]");
        goto end;
    }
    cJSON_AddItemToObject(item, "scheduledCommunicationTime", scheduled_communication_time_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [scheduled_communication_time]");
        goto end;
    }
    }

    if (expected_ue_behaviour_data_1->scheduled_communication_type != OpenAPI_scheduled_communication_type_NULL) {
    if (cJSON_AddStringToObject(item, "scheduledCommunicationType", OpenAPI_scheduled_communication_type_ToString(expected_ue_behaviour_data_1->scheduled_communication_type)) == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [scheduled_communication_type]");
        goto end;
    }
    }

    if (expected_ue_behaviour_data_1->expected_umts) {
    cJSON *expected_umtsList = cJSON_AddArrayToObject(item, "expectedUmts");
    if (expected_umtsList == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [expected_umts]");
        goto end;
    }
    OpenAPI_list_for_each(expected_ue_behaviour_data_1->expected_umts, node) {
        cJSON *itemLocal = OpenAPI_location_area_1_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [expected_umts]");
            goto end;
        }
        cJSON_AddItemToArray(expected_umtsList, itemLocal);
    }
    }

    if (expected_ue_behaviour_data_1->traffic_profile != OpenAPI_traffic_profile_NULL) {
    if (cJSON_AddStringToObject(item, "trafficProfile", OpenAPI_traffic_profile_ToString(expected_ue_behaviour_data_1->traffic_profile)) == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [traffic_profile]");
        goto end;
    }
    }

    if (expected_ue_behaviour_data_1->battery_indication) {
    cJSON *battery_indication_local_JSON = OpenAPI_battery_indication_convertToJSON(expected_ue_behaviour_data_1->battery_indication);
    if (battery_indication_local_JSON == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [battery_indication]");
        goto end;
    }
    cJSON_AddItemToObject(item, "batteryIndication", battery_indication_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [battery_indication]");
        goto end;
    }
    }

    if (expected_ue_behaviour_data_1->validity_time) {
    if (cJSON_AddStringToObject(item, "validityTime", expected_ue_behaviour_data_1->validity_time) == NULL) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed [validity_time]");
        goto end;
    }
    }

end:
    return item;
}

OpenAPI_expected_ue_behaviour_data_1_t *OpenAPI_expected_ue_behaviour_data_1_parseFromJSON(cJSON *expected_ue_behaviour_data_1JSON)
{
    OpenAPI_expected_ue_behaviour_data_1_t *expected_ue_behaviour_data_1_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *stationary_indication = NULL;
    OpenAPI_stationary_indication_e stationary_indicationVariable = 0;
    cJSON *communication_duration_time = NULL;
    cJSON *periodic_time = NULL;
    cJSON *scheduled_communication_time = NULL;
    OpenAPI_scheduled_communication_time_1_t *scheduled_communication_time_local_nonprim = NULL;
    cJSON *scheduled_communication_type = NULL;
    OpenAPI_scheduled_communication_type_e scheduled_communication_typeVariable = 0;
    cJSON *expected_umts = NULL;
    OpenAPI_list_t *expected_umtsList = NULL;
    cJSON *traffic_profile = NULL;
    OpenAPI_traffic_profile_e traffic_profileVariable = 0;
    cJSON *battery_indication = NULL;
    OpenAPI_battery_indication_t *battery_indication_local_nonprim = NULL;
    cJSON *validity_time = NULL;
    stationary_indication = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "stationaryIndication");
    if (stationary_indication) {
    if (!cJSON_IsString(stationary_indication)) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_parseFromJSON() failed [stationary_indication]");
        goto end;
    }
    stationary_indicationVariable = OpenAPI_stationary_indication_FromString(stationary_indication->valuestring);
    }

    communication_duration_time = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "communicationDurationTime");
    if (communication_duration_time) {
    if (!cJSON_IsNumber(communication_duration_time)) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_parseFromJSON() failed [communication_duration_time]");
        goto end;
    }
    }

    periodic_time = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "periodicTime");
    if (periodic_time) {
    if (!cJSON_IsNumber(periodic_time)) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_parseFromJSON() failed [periodic_time]");
        goto end;
    }
    }

    scheduled_communication_time = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "scheduledCommunicationTime");
    if (scheduled_communication_time) {
    scheduled_communication_time_local_nonprim = OpenAPI_scheduled_communication_time_1_parseFromJSON(scheduled_communication_time);
    if (!scheduled_communication_time_local_nonprim) {
        ogs_error("OpenAPI_scheduled_communication_time_1_parseFromJSON failed [scheduled_communication_time]");
        goto end;
    }
    }

    scheduled_communication_type = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "scheduledCommunicationType");
    if (scheduled_communication_type) {
    if (!cJSON_IsString(scheduled_communication_type)) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_parseFromJSON() failed [scheduled_communication_type]");
        goto end;
    }
    scheduled_communication_typeVariable = OpenAPI_scheduled_communication_type_FromString(scheduled_communication_type->valuestring);
    }

    expected_umts = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "expectedUmts");
    if (expected_umts) {
        cJSON *expected_umts_local = NULL;
        if (!cJSON_IsArray(expected_umts)) {
            ogs_error("OpenAPI_expected_ue_behaviour_data_1_parseFromJSON() failed [expected_umts]");
            goto end;
        }

        expected_umtsList = OpenAPI_list_create();

        cJSON_ArrayForEach(expected_umts_local, expected_umts) {
            if (!cJSON_IsObject(expected_umts_local)) {
                ogs_error("OpenAPI_expected_ue_behaviour_data_1_parseFromJSON() failed [expected_umts]");
                goto end;
            }
            OpenAPI_location_area_1_t *expected_umtsItem = OpenAPI_location_area_1_parseFromJSON(expected_umts_local);
            if (!expected_umtsItem) {
                ogs_error("No expected_umtsItem");
                goto end;
            }
            OpenAPI_list_add(expected_umtsList, expected_umtsItem);
        }
    }

    traffic_profile = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "trafficProfile");
    if (traffic_profile) {
    if (!cJSON_IsString(traffic_profile)) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_parseFromJSON() failed [traffic_profile]");
        goto end;
    }
    traffic_profileVariable = OpenAPI_traffic_profile_FromString(traffic_profile->valuestring);
    }

    battery_indication = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "batteryIndication");
    if (battery_indication) {
    battery_indication_local_nonprim = OpenAPI_battery_indication_parseFromJSON(battery_indication);
    if (!battery_indication_local_nonprim) {
        ogs_error("OpenAPI_battery_indication_parseFromJSON failed [battery_indication]");
        goto end;
    }
    }

    validity_time = cJSON_GetObjectItemCaseSensitive(expected_ue_behaviour_data_1JSON, "validityTime");
    if (validity_time) {
    if (!cJSON_IsString(validity_time) && !cJSON_IsNull(validity_time)) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_parseFromJSON() failed [validity_time]");
        goto end;
    }
    }

    expected_ue_behaviour_data_1_local_var = OpenAPI_expected_ue_behaviour_data_1_create (
        stationary_indication ? stationary_indicationVariable : 0,
        communication_duration_time ? true : false,
        communication_duration_time ? communication_duration_time->valuedouble : 0,
        periodic_time ? true : false,
        periodic_time ? periodic_time->valuedouble : 0,
        scheduled_communication_time ? scheduled_communication_time_local_nonprim : NULL,
        scheduled_communication_type ? scheduled_communication_typeVariable : 0,
        expected_umts ? expected_umtsList : NULL,
        traffic_profile ? traffic_profileVariable : 0,
        battery_indication ? battery_indication_local_nonprim : NULL,
        validity_time && !cJSON_IsNull(validity_time) ? ogs_strdup(validity_time->valuestring) : NULL
    );

    return expected_ue_behaviour_data_1_local_var;
end:
    if (scheduled_communication_time_local_nonprim) {
        OpenAPI_scheduled_communication_time_1_free(scheduled_communication_time_local_nonprim);
        scheduled_communication_time_local_nonprim = NULL;
    }
    if (expected_umtsList) {
        OpenAPI_list_for_each(expected_umtsList, node) {
            OpenAPI_location_area_1_free(node->data);
        }
        OpenAPI_list_free(expected_umtsList);
        expected_umtsList = NULL;
    }
    if (battery_indication_local_nonprim) {
        OpenAPI_battery_indication_free(battery_indication_local_nonprim);
        battery_indication_local_nonprim = NULL;
    }
    return NULL;
}

OpenAPI_expected_ue_behaviour_data_1_t *OpenAPI_expected_ue_behaviour_data_1_copy(OpenAPI_expected_ue_behaviour_data_1_t *dst, OpenAPI_expected_ue_behaviour_data_1_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_expected_ue_behaviour_data_1_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_expected_ue_behaviour_data_1_convertToJSON() failed");
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

    OpenAPI_expected_ue_behaviour_data_1_free(dst);
    dst = OpenAPI_expected_ue_behaviour_data_1_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

