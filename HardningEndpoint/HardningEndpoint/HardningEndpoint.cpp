#include <string>
#include "HardningEndpoint_t.h"
#include "sgx_trts.h"

void Encryption(char uData[100])
{
	char key = 'K';

	for (unsigned int i = 0; i <strlen(uData); i++)
	{
		uData[i] = uData[i] ^ key;
	}
}

void Decryption(char eData[100])
{
	char key = 'K';

	for (unsigned int i = 0; i <strlen(eData); i++)
	{
		eData[i] = eData[i] ^ key;
	}
}

void SecretInfo(char *buf, size_t len)
{
	const char *secret = "Hello Enclave!";
	if (len > strlen(secret))
	{
		memcpy(buf, secret, strlen(secret) + 1);
	}
}