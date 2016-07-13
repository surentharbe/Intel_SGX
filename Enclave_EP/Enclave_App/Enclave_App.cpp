#include <iostream>
#include <string>
#include <tchar.h>
#include "sgx_urts.h"
#include "Enclave_EP_u.h"
#define ENCLAVE_FILE _T("Enclave_EP.signed.dll")
#define MAX_BUF_LEN 100
#define MIN_BUF_LEN 50
#pragma warning(disable: 4996)
using namespace std;

int main()
{
	sgx_status_t sgx_stat = SGX_SUCCESS;
	sgx_enclave_id_t eid = 0;
	sgx_launch_token_t token ={0};
	int updated = 0;
	char uName[MIN_BUF_LEN], uPassword[MIN_BUF_LEN];
	char uData[MAX_BUF_LEN];
	//char *uData = new char[MAX_BUF_LEN];
	//char *retValue;

	sgx_stat = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG,&token,&updated,&eid,NULL);

	if (sgx_stat != SGX_SUCCESS) 
	{
		cout<<"App: error %#x, failed to create enclave.\n"<< sgx_stat;
		return -1;
	}

	cout<<"\n\tEnter the User Creditional\n";
	cout<<"USERNAME:";
	cin>>uName;
	cout<<"PASSWORD:";
	cin>>uPassword;
	
	strcpy(uData,uName);
	strcat(uData,uPassword);

	//EndPoint_TrustedFn(eid, &retValue, uData);
	//cout<<"Return Value: "<<retValue<<endl;
	EndPoint_TrustedFn(eid, uData);
	cout<<"Return Value: "<<uData<<endl;
	

	if(SGX_SUCCESS != sgx_destroy_enclave(eid))
		return -1;

	return 0;
}
