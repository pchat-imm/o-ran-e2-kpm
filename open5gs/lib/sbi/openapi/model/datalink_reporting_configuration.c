
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "datalink_reporting_configuration.h"

OpenAPI_datalink_reporting_configuration_t *OpenAPI_datalink_reporting_configuration_create(
    OpenAPI_list_t *ddd_traffic_des,
    char *dnn,
    OpenAPI_snssai_t *slice,
    OpenAPI_list_t *ddd_status_list
)
{
    OpenAPI_datalink_reporting_configuration_t *datalink_reporting_configuration_local_var = ogs_malloc(sizeof(OpenAPI_datalink_reporting_configuration_t));
    ogs_assert(datalink_reporting_configuration_local_var);

    datalink_reporting_configuration_local_var->ddd_traffic_des = ddd_traffic_des;
    datalink_reporting_configuration_local_var->dnn = dnn;
    datalink_reporting_configuration_local_var->slice = slice;
    datalink_reporting_configuration_local_var->ddd_status_list = ddd_status_list;

    return datalink_reporting_configuration_local_var;
}

void OpenAPI_datalink_reporting_configuration_free(OpenAPI_datalink_reporting_configuration_t *datalink_reporting_configuration)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == datalink_reporting_configuration) {
        return;
    }
    if (datalink_reporting_configuration->ddd_traffic_des) {
        OpenAPI_list_for_each(datalink_reporting_configuration->ddd_traffic_des, node) {
            OpenAPI_ddd_traffic_descriptor_free(node->data);
        }
        OpenAPI_list_free(datalink_reporting_configuration->ddd_traffic_des);
        datalink_reporting_configuration->ddd_traffic_des = NULL;
    }
    if (datalink_reporting_configuration->dnn) {
        ogs_free(datalink_reporting_configuration->dnn);
        datalink_reporting_configuration->dnn = NULL;
    }
    if (datalink_reporting_configuration->slice) {
        OpenAPI_snssai_free(datalink_reporting_configuration->slice);
        datalink_reporting_configuration->slice = NULL;
    }
    if (datalink_reporting_configuration->ddd_status_list) {
        OpenAPI_list_free(datalink_reporting_configuration->ddd_status_list);
        datalink_reporting_configuration->ddd_status_list = NULL;
    }
    ogs_free(datalink_reporting_configuration);
}

cJSON *OpenAPI_datalink_reporting_configuration_convertToJSON(OpenAPI_datalink_reporting_configuration_t *datalink_reporting_configuration)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (datalink_reporting_configuration == NULL) {
        ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed [DatalinkReportingConfiguration]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (datalink_reporting_configuration->ddd_traffic_des) {
    cJSON *ddd_traffic_desList = cJSON_AddArrayToObject(item, "dddTrafficDes");
    if (ddd_traffic_desList == NULL) {
        ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed [ddd_traffic_des]");
        goto end;
    }
    OpenAPI_list_for_each(datalink_reporting_configuration->ddd_traffic_des, node) {
        cJSON *itemLocal = OpenAPI_ddd_traffic_descriptor_convertToJSON(node->data);
        if (itemLocal == NULL) {
            ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed [ddd_traffic_des]");
            goto end;
        }
        cJSON_AddItemToArray(ddd_traffic_desList, itemLocal);
    }
    }

    if (datalink_reporting_configuration->dnn) {
    if (cJSON_AddStringToObject(item, "dnn", datalink_reporting_configuration->dnn) == NULL) {
        ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed [dnn]");
        goto end;
    }
    }

    if (datalink_reporting_configuration->slice) {
    cJSON *slice_local_JSON = OpenAPI_snssai_convertToJSON(datalink_reporting_configuration->slice);
    if (slice_local_JSON == NULL) {
        ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed [slice]");
        goto end;
    }
    cJSON_AddItemToObject(item, "slice", slice_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed [slice]");
        goto end;
    }
    }

    if (datalink_reporting_configuration->ddd_status_list != OpenAPI_dl_data_delivery_status_NULL) {
    cJSON *ddd_status_listList = cJSON_AddArrayToObject(item, "dddStatusList");
    if (ddd_status_listList == NULL) {
        ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed [ddd_status_list]");
        goto end;
    }
    OpenAPI_list_for_each(datalink_reporting_configuration->ddd_status_list, node) {
        if (cJSON_AddStringToObject(ddd_status_listList, "", OpenAPI_dl_data_delivery_status_ToString((intptr_t)node->data)) == NULL) {
            ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed [ddd_status_list]");
            goto end;
        }
    }
    }

end:
    return item;
}

OpenAPI_datalink_reporting_configuration_t *OpenAPI_datalink_reporting_configuration_parseFromJSON(cJSON *datalink_reporting_configurationJSON)
{
    OpenAPI_datalink_reporting_configuration_t *datalink_reporting_configuration_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *ddd_traffic_des = NULL;
    OpenAPI_list_t *ddd_traffic_desList = NULL;
    cJSON *dnn = NULL;
    cJSON *slice = NULL;
    OpenAPI_snssai_t *slice_local_nonprim = NULL;
    cJSON *ddd_status_list = NULL;
    OpenAPI_list_t *ddd_status_listList = NULL;
    ddd_traffic_des = cJSON_GetObjectItemCaseSensitive(datalink_reporting_configurationJSON, "dddTrafficDes");
    if (ddd_traffic_des) {
        cJSON *ddd_traffic_des_local = NULL;
        if (!cJSON_IsArray(ddd_traffic_des)) {
            ogs_error("OpenAPI_datalink_reporting_configuration_parseFromJSON() failed [ddd_traffic_des]");
            goto end;
        }

        ddd_traffic_desList = OpenAPI_list_create();

        cJSON_ArrayForEach(ddd_traffic_des_local, ddd_traffic_des) {
            if (!cJSON_IsObject(ddd_traffic_des_local)) {
                ogs_error("OpenAPI_datalink_reporting_configuration_parseFromJSON() failed [ddd_traffic_des]");
                goto end;
            }
            OpenAPI_ddd_traffic_descriptor_t *ddd_traffic_desItem = OpenAPI_ddd_traffic_descriptor_parseFromJSON(ddd_traffic_des_local);
            if (!ddd_traffic_desItem) {
                ogs_error("No ddd_traffic_desItem");
                goto end;
            }
            OpenAPI_list_add(ddd_traffic_desList, ddd_traffic_desItem);
        }
    }

    dnn = cJSON_GetObjectItemCaseSensitive(datalink_reporting_configurationJSON, "dnn");
    if (dnn) {
    if (!cJSON_IsString(dnn) && !cJSON_IsNull(dnn)) {
        ogs_error("OpenAPI_datalink_reporting_configuration_parseFromJSON() failed [dnn]");
        goto end;
    }
    }

    slice = cJSON_GetObjectItemCaseSensitive(datalink_reporting_configurationJSON, "slice");
    if (slice) {
    slice_local_nonprim = OpenAPI_snssai_parseFromJSON(slice);
    if (!slice_local_nonprim) {
        ogs_error("OpenAPI_snssai_parseFromJSON failed [slice]");
        goto end;
    }
    }

    ddd_status_list = cJSON_GetObjectItemCaseSensitive(datalink_reporting_configurationJSON, "dddStatusList");
    if (ddd_status_list) {
        cJSON *ddd_status_list_local = NULL;
        if (!cJSON_IsArray(ddd_status_list)) {
            ogs_error("OpenAPI_datalink_reporting_configuration_parseFromJSON() failed [ddd_status_list]");
            goto end;
        }

        ddd_status_listList = OpenAPI_list_create();

        cJSON_ArrayForEach(ddd_status_list_local, ddd_status_list) {
            if (!cJSON_IsString(ddd_status_list_local)) {
                ogs_error("OpenAPI_datalink_reporting_configuration_parseFromJSON() failed [ddd_status_list]");
                goto end;
            }
            OpenAPI_list_add(ddd_status_listList, (void *)OpenAPI_dl_data_delivery_status_FromString(ddd_status_list_local->valuestring));
        }
    }

    datalink_reporting_configuration_local_var = OpenAPI_datalink_reporting_configuration_create (
        ddd_traffic_des ? ddd_traffic_desList : NULL,
        dnn && !cJSON_IsNull(dnn) ? ogs_strdup(dnn->valuestring) : NULL,
        slice ? slice_local_nonprim : NULL,
        ddd_status_list ? ddd_status_listList : NULL
    );

    return datalink_reporting_configuration_local_var;
end:
    if (ddd_traffic_desList) {
        OpenAPI_list_for_each(ddd_traffic_desList, node) {
            OpenAPI_ddd_traffic_descriptor_free(node->data);
        }
        OpenAPI_list_free(ddd_traffic_desList);
        ddd_traffic_desList = NULL;
    }
    if (slice_local_nonprim) {
        OpenAPI_snssai_free(slice_local_nonprim);
        slice_local_nonprim = NULL;
    }
    if (ddd_status_listList) {
        OpenAPI_list_free(ddd_status_listList);
        ddd_status_listList = NULL;
    }
    return NULL;
}

OpenAPI_datalink_reporting_configuration_t *OpenAPI_datalink_reporting_configuration_copy(OpenAPI_datalink_reporting_configuration_t *dst, OpenAPI_datalink_reporting_configuration_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_datalink_reporting_configuration_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_datalink_reporting_configuration_convertToJSON() failed");
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

    OpenAPI_datalink_reporting_configuration_free(dst);
    dst = OpenAPI_datalink_reporting_configuration_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

