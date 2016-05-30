#include "Enclave_Simulation_u.h"

typedef struct ms_TrustedFn_t {
	char* ms_buf;
	size_t ms_len;
} ms_TrustedFn_t;

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_Enclave_Simulation = {
	0,
	{ NULL },
};

sgx_status_t TrustedFn(sgx_enclave_id_t eid, char* buf, size_t len)
{
	sgx_status_t status;
	ms_TrustedFn_t ms;
	ms.ms_buf = buf;
	ms.ms_len = len;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave_Simulation, &ms);
	return status;
}

