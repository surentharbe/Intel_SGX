#include "HardningEndpoint_u.h"

typedef struct ms_Encryption_t {
	char* ms_uData;
} ms_Encryption_t;

typedef struct ms_Decryption_t {
	char* ms_euData;
} ms_Decryption_t;

typedef struct ms_SecretInfo_t {
	char* ms_buf;
	size_t ms_len;
} ms_SecretInfo_t;

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_HardningEndpoint = {
	0,
	{ NULL },
};

sgx_status_t Encryption(sgx_enclave_id_t eid, char uData[100])
{
	sgx_status_t status;
	ms_Encryption_t ms;
	ms.ms_uData = (char*)uData;
	status = sgx_ecall(eid, 0, &ocall_table_HardningEndpoint, &ms);
	return status;
}

sgx_status_t Decryption(sgx_enclave_id_t eid, char euData[100])
{
	sgx_status_t status;
	ms_Decryption_t ms;
	ms.ms_euData = (char*)euData;
	status = sgx_ecall(eid, 1, &ocall_table_HardningEndpoint, &ms);
	return status;
}

sgx_status_t SecretInfo(sgx_enclave_id_t eid, char* buf, size_t len)
{
	sgx_status_t status;
	ms_SecretInfo_t ms;
	ms.ms_buf = buf;
	ms.ms_len = len;
	status = sgx_ecall(eid, 2, &ocall_table_HardningEndpoint, &ms);
	return status;
}

