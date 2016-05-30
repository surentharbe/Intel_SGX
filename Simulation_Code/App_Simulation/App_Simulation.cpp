#include <stdio.h>
#include <tchar.h>
#include "sgx_urts.h"
#include "Enclave_Simulation_u.h"
#define ENCLAVE_FILE _T("Enclave_Simulation.signed.dll")
#define MAX_BUF_LEN 100

int _tmain(int argc, _TCHAR* argv[])
{
	sgx_status_t sgx_stat = SGX_SUCCESS;
	sgx_enclave_id_t eid = 0;
	sgx_launch_token_t token ={0};
	int updated = 0;
	char buffer[MAX_BUF_LEN] = "Hello World!";


	// Create the Enclave with above launch token.
	sgx_stat = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);

	if (sgx_stat != SGX_SUCCESS) 
	{
		printf("App: error %#x, failed to create enclave.\n", sgx_stat);
		return -1;
	}

	// A bunch of Enclave calls (ECALL) will happen here.
	TrustedFn(eid, buffer, MAX_BUF_LEN);
	printf("%s", buffer);

	// Destroy the enclave when all Enclave calls finished.
	if(SGX_SUCCESS != sgx_destroy_enclave(eid))
	{
		return -1;
	}
	return 0;
}