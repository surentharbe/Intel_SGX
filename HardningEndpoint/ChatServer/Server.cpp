#include "Server.h"

WSockServer::WSockServer(int RequestVersion)
{
	hSocket = INVALID_SOCKET;
	ClientSocket = INVALID_SOCKET;

	if(WSAStartup(MAKEWORD(RequestVersion, 0), &wsaData) == 0)		// Check required version
	{
		if(LOBYTE(wsaData.wVersion < RequestVersion))
		{
			throw "Requested version not available.";
		}
	}
	else
		throw "Startup failed.";
}

WSockServer::~WSockServer()
{
	if(WSACleanup() != 0)
		throw "Cleanup failed.";
	if(hSocket != INVALID_SOCKET)
		closesocket(hSocket);
	if(ClientSocket != INVALID_SOCKET)
		closesocket(hSocket);
}


void WSockServer::SetServerSockAddr(sockaddr_in *sockAddr, int PortNumber)
{
	sockAddr->sin_addr.S_un.S_addr = INADDR_ANY;			// Listen on all available ip's
	sockAddr->sin_family = AF_INET;
	sockAddr->sin_port = htons(PortNumber);	
}


bool WSockServer::RunServer(int PortNumber)
{	
	if((hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)		// Create socket
		throw "Could not create socket.";

	SetServerSockAddr(&sockAddr, PortNumber);	// Fill sockAddr

	if(bind(hSocket, (sockaddr*)(&sockAddr), sizeof(sockAddr)) != 0)
		throw "Could not bind socket.";

	if(listen(hSocket, SOMAXCONN) != 0)
		throw "Could not put the socket in listening mode.";

	cout<<"\n##################################################"<<endl;
	cout << "\tServer Information" << endl;
	cout << "Server IP Address: " << inet_ntoa(sockAddr.sin_addr) << endl;
	cout << "Server PORT Number: " << ntohs(sockAddr.sin_port) << endl;
	cout<<"##################################################"<<endl;

	int SizeAddr = sizeof(ClientAddr);

	cout << "Waiting for clients to Connect... "<<endl;
	ClientSocket = accept(hSocket, (sockaddr*)(&ClientAddr), &SizeAddr);
	cout << "Client Found!!!" << endl;
	
	return true;
}

void WSockServer::StartChat()
{
	while(true)
	{
		int BytesRec = recv(ClientSocket, Buffer, sizeof(Buffer), 0);

		if(BytesRec == 0)
		{
			cout << "\nThe client closed the connection. " << endl;
			break;
		}
		else if(BytesRec == SOCKET_ERROR)
		{
			throw "The client seems to be offline.";
		}
		else
		{
			Buffer[BytesRec] = 0;
			cout<<"\nInformation Received From Client: "<<endl;
			cout<< "\t" << Buffer << endl;
		}
	}
}




