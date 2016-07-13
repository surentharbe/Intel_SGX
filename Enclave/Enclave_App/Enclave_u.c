#include "Enclave_u.h"

typedef struct ms_enclaveChangeBuffer_t {
	char* ms_buf;
	size_t ms_len;
} ms_enclaveChangeBuffer_t;

typedef struct ms_enclaveStringSave_t {
	char* ms_input;
	size_t ms_len;
} ms_enclaveStringSave_t;

typedef struct ms_enclaveStringLoad_t {
	char* ms_output;
	size_t ms_len;
} ms_enclaveStringLoad_t;

typedef struct ms_enclaveSaveInt_t {
	int ms_input;
} ms_enclaveSaveInt_t;

typedef struct ms_enclaveLoadInt_t {
	int ms_retval;
} ms_enclaveLoadInt_t;

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_Enclave = {
	0,
	{ NULL },
};

sgx_status_t enclaveChangeBuffer(sgx_enclave_id_t eid, char* buf, size_t len)
{
	sgx_status_t status;
	ms_enclaveChangeBuffer_t ms;
	ms.ms_buf = buf;
	ms.ms_len = len;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t enclaveStringSave(sgx_enclave_id_t eid, char* input, size_t len)
{
	sgx_status_t status;
	ms_enclaveStringSave_t ms;
	ms.ms_input = input;
	ms.ms_len = len;
	status = sgx_ecall(eid, 1, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t enclaveStringLoad(sgx_enclave_id_t eid, char* output, size_t len)
{
	sgx_status_t status;
	ms_enclaveStringLoad_t ms;
	ms.ms_output = output;
	ms.ms_len = len;
	status = sgx_ecall(eid, 2, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t enclaveSaveInt(sgx_enclave_id_t eid, int input)
{
	sgx_status_t status;
	ms_enclaveSaveInt_t ms;
	ms.ms_input = input;
	status = sgx_ecall(eid, 3, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t enclaveLoadInt(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_enclaveLoadInt_t ms;
	status = sgx_ecall(eid, 4, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

