#include "Sample_Enclave_t.h"
#include "sgx_trts.h"
#include <string.h>

void foo(char *buf, size_t len)
{
	const char *secret = "Hello Enclave!";
	if (len > strlen(secret))
	{
		memcpy(buf, secret, strlen(secret) + 1);
	}
}