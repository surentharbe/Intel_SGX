#ifndef ENCLAVE_EP_U_H__
#define ENCLAVE_EP_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


sgx_status_t EndPoint_TrustedFn(sgx_enclave_id_t eid, char uData[100]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
