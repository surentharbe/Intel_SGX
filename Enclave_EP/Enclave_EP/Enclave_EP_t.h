#ifndef ENCLAVE_EP_T_H__
#define ENCLAVE_EP_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


void EndPoint_TrustedFn(char uData[100]);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
