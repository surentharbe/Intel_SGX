#ifndef HARDNINGENDPOINT_U_H__
#define HARDNINGENDPOINT_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


sgx_status_t Encryption(sgx_enclave_id_t eid, char uData[100]);
sgx_status_t Decryption(sgx_enclave_id_t eid, char euData[100]);
sgx_status_t SecretInfo(sgx_enclave_id_t eid, char* buf, size_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
