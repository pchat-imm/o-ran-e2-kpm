/*
 * sec_param_exch_rsp_data.h
 *
 * Response data structure for parameter exchange
 */

#ifndef _OpenAPI_sec_param_exch_rsp_data_H_
#define _OpenAPI_sec_param_exch_rsp_data_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ipx_provider_sec_info.h"
#include "protection_policy.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_sec_param_exch_rsp_data_s OpenAPI_sec_param_exch_rsp_data_t;
typedef struct OpenAPI_sec_param_exch_rsp_data_s {
    char *n32f_context_id;
    char *selected_jwe_cipher_suite;
    char *selected_jws_cipher_suite;
    struct OpenAPI_protection_policy_s *sel_protection_policy_info;
    OpenAPI_list_t *ipx_provider_sec_info_list;
    char *sender;
} OpenAPI_sec_param_exch_rsp_data_t;

OpenAPI_sec_param_exch_rsp_data_t *OpenAPI_sec_param_exch_rsp_data_create(
    char *n32f_context_id,
    char *selected_jwe_cipher_suite,
    char *selected_jws_cipher_suite,
    OpenAPI_protection_policy_t *sel_protection_policy_info,
    OpenAPI_list_t *ipx_provider_sec_info_list,
    char *sender
);
void OpenAPI_sec_param_exch_rsp_data_free(OpenAPI_sec_param_exch_rsp_data_t *sec_param_exch_rsp_data);
OpenAPI_sec_param_exch_rsp_data_t *OpenAPI_sec_param_exch_rsp_data_parseFromJSON(cJSON *sec_param_exch_rsp_dataJSON);
cJSON *OpenAPI_sec_param_exch_rsp_data_convertToJSON(OpenAPI_sec_param_exch_rsp_data_t *sec_param_exch_rsp_data);
OpenAPI_sec_param_exch_rsp_data_t *OpenAPI_sec_param_exch_rsp_data_copy(OpenAPI_sec_param_exch_rsp_data_t *dst, OpenAPI_sec_param_exch_rsp_data_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_sec_param_exch_rsp_data_H_ */

