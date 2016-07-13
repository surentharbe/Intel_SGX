#ifndef __SERVER_H__
#define __SERVER_H__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
using namespace std;

class WSockServer
{
public:
	WSockServer(int RequestVersion);
	~WSockServer();

	bool RunServer(int PortNumber);			// Run te server
	void StartChat();						// Start communication
private:
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKET ClientSocket;
	sockaddr_in sockAddr;
	sockaddr_in ClientAddr;

	char Buffer[128];
	void SetServerSockAddr(sockaddr_in *sockAddr, int PortNumber);
};


#endif