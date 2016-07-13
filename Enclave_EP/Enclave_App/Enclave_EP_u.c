#include "Enclave_EP_u.h"

typedef struct ms_EndPoint_TrustedFn_t {
	char* ms_uData;
} ms_EndPoint_TrustedFn_t;

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_Enclave_EP = {
	0,
	{ NULL },
};

sgx_status_t EndPoint_TrustedFn(sgx_enclave_id_t eid, char uData[100])
{
	sgx_status_t status;
	ms_EndPoint_TrustedFn_t ms;
	ms.ms_uData = (char*)uData;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave_EP, &ms);
	return status;
}

