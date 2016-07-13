#ifndef HARDNINGENDPOINT_T_H__
#define HARDNINGENDPOINT_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


void Encryption(char uData[100]);
void Decryption(char euData[100]);
void SecretInfo(char* buf, size_t len);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
