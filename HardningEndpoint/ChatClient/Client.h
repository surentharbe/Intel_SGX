#ifndef CLIENT_H__
#define CLIENT_H__

#include <windows.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include "sgx_urts.h"
#include "HardningEndpoint_u.h"
#define ENCLAVE_FILE _T("HardningEndpoint.signed.dll")
#define MAX_BUF_LEN 100
#define MIN_BUF_LEN 50
#pragma warning(disable: 4996)
#define REQ_WINSOCK_VER	2
#define PORT			4444
using namespace std;

class WSockClient
{
public:
	WSockClient(int RequestVersion);						//Constructor
	~WSockClient();											//Destructor
	bool ConnectServer(int PortNumber, char *IP);			// Connect to the server
	void StartChat();										// Start the communication
private:
	WSADATA wsaData;
	SOCKET hSocket;
	sockaddr_in sockAddr;
	void SetClientSockAddr(sockaddr_in *sockAddr, int PortNumber, char *IP);		// Fill the sockAddr structure
};

#endif