/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2AP-PDU-Contents"
 * 	found in "e2ap-v02.03.asn1"
 * 	`asn1c -gen-PER -no-gen-OER -fcompound-names -no-gen-example -findirect-choice -fno-include-deps`
 */

#ifndef	_ResetResponse_H_
#define	_ResetResponse_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ProtocolIE-Container.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ResetResponse */
typedef struct ResetResponse {
	ProtocolIE_Container_2153P27_t	 protocolIEs;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ResetResponse_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ResetResponse;
extern asn_SEQUENCE_specifics_t asn_SPC_ResetResponse_specs_1;
extern asn_TYPE_member_t asn_MBR_ResetResponse_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _ResetResponse_H_ */
#include <asn_internal.h>