#ifndef ENCLAVE_SIMULATION_T_H__
#define ENCLAVE_SIMULATION_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


void TrustedFn(char* buf, size_t len);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
