#include <string>
#include "Enclave_EP_t.h"
#include "sgx_trts.h"

//void EndPoint_TrustedFn(char uData[100])
//{
//	char key = 'K';
//    
//    for (unsigned int i = 0; i < strlen(uData); i++)
//	{
//        uData[i] = uData[i] ^ key;
//	}
//    
//    //return 0;
//}

void EndPoint_TrustedFn(char uData[100])
{
	char key = 'K';
    
    for (unsigned int i = 0; i <strlen(uData); i++)
	{
        uData[i] = uData[i] ^ key;
	}
}