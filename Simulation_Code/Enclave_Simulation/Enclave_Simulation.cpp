#include "Enclave_Simulation_t.h"
#include "sgx_trts.h"
#include <string.h>

//Get the secrat value from enclave using TrustedFn() Call.
void TrustedFn(char *buf, size_t len)
{
	const char *secret = "Hello Enclave!";

	if (len > strlen(secret))
	{
		memcpy(buf, secret, strlen(secret) + 1);
	}
}
