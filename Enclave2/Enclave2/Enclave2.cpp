#include "Enclave2_t.h"
#include "sgx_trts.h"

#include <cstring>

char savedString[100] = "Default Enclave savedText";
int savedInt = -1;

// change a buffer with a constant string
void enclaveChangeBuffer(char *buf, size_t len)
{
	const char *secret = "Hello Enclave!";
	if (len > strlen(secret))
	{
		memcpy(buf, secret, strlen(secret) + 1);
	} 
	else 
	{
		memcpy(buf, "false", strlen("false") + 1);
	}
}

// write a var to the buffer
void enclaveStringSave(char *input, size_t len) 
{
	if ((strlen(input) + 1) < 100)
	{
		memcpy(savedString, input, strlen(input) + 1);      
	} 
	else 
	{
		memcpy(input, "false", strlen("false") + 1);
	}
}

// save the buffer to a var
void enclaveStringLoad(char *output, size_t len) 
{
	if (len > strlen(savedString))
	{
		memcpy(output, savedString, strlen(savedString) + 1);
	} 
	else 
	{
		memcpy(output, "false", strlen("false") + 1);
	}
}

// save a int to a var
void enclaveSaveInt(int input) 
{
	savedInt = input;
}

// return a var
int enclaveLoadInt()
{
	return savedInt;
}