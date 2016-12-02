// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "sgx_urts.h"
#include "Enclave2_u.h"
#include <stdio.h>
#include <tchar.h>

#define ENCLAVE_FILE _T("Enclave2.signed.dll")
#define MAX_BUF_LEN 100

int main()
{
    sgx_enclave_id_t   eid;
    sgx_status_t       ret   = SGX_SUCCESS;
    sgx_launch_token_t token = {0};
    int updated = 0;
    char buffer[MAX_BUF_LEN] = "Hello World!";
    char secret[MAX_BUF_LEN] = "My secret string";
    char retSecret[MAX_BUF_LEN] = "";
    int secretIntValue = 0;
    int *secretIntPointer = &secretIntValue;

    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);

    if (ret != SGX_SUCCESS) 
	{
        printf("\nApp: error %#x, failed to create enclave.\n", ret);
    }

    // A bunch of Enclave calls (ECALL) will happen here.

    printf("\nApp: Buffertests:\n");

    // Change the buffer in the enclave
    printf("App: Buffer before change: %s\n", buffer);
    enclaveChangeBuffer(eid, buffer, MAX_BUF_LEN);
    printf("App: Buffer after change: %s\n", buffer);


    printf("\nApp: Stringtests:\n");

    // Load a string from enclave
    // should return the default savedString from the enclave
    enclaveStringLoad(eid, retSecret, MAX_BUF_LEN);
    printf("App: Returned Secret: %s\n", retSecret);

    // Save a string in the enclave
    enclaveStringSave(eid, secret, strlen(secret)+1);
    printf("App: Saved Secret: %s\n", secret);

    // Load a string from enclave
    // should return our secret string 
    enclaveStringLoad(eid, retSecret, MAX_BUF_LEN);
    printf("App: Load Secret: %s\n", retSecret);


    printf("\nApp: Integertests:\n");

    // Load integer from enclave
    // should return defauld savedInt from enclave
    enclaveLoadInt(eid, secretIntPointer);
    printf("App: secretIntValue first load: %d\n", secretIntValue);

    // Save integer to enclave
    enclaveSaveInt(eid, 1337);
    printf("App: saved a 1337 to the enclave. \n", 1337);

    // Load integer from enclave
    // should return our saved 1337
    enclaveLoadInt(eid, secretIntPointer);
    printf("App: secretIntValue second load after 1337 was saved: %d\n", secretIntValue);


    // Destroy the enclave when all Enclave calls finished.
    if(SGX_SUCCESS != sgx_destroy_enclave(eid))
        printf("\nApp: error, failed to destroy enclave.\n");

    getchar();
    return 0;
}