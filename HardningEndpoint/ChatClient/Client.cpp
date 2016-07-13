#include "Client.h"

WSockClient::WSockClient(int RequestVersion)
{
	hSocket = INVALID_SOCKET;

	if(WSAStartup(MAKEWORD(RequestVersion, 0), &wsaData) == 0)
	{
		if(LOBYTE(wsaData.wVersion < RequestVersion))
		{
			throw "Requested version not available.";
		}
	}
	else
		throw "Startup failed.";
}

WSockClient::~WSockClient()
{
	if(WSACleanup() != 0)
		throw "Cleanup failed.";
	if(hSocket != INVALID_SOCKET)
		closesocket(hSocket);
}

void WSockClient::SetClientSockAddr(sockaddr_in *sockAddr, int PortNumber, char *IP)
{
	sockAddr->sin_addr.S_un.S_addr = inet_addr(IP);
	sockAddr->sin_family = AF_INET;						// Use TCP/IP protocol
	sockAddr->sin_port = htons(PortNumber);
}

bool WSockClient::ConnectServer(int PortNumber, char *IP)
{
	SetClientSockAddr(&sockAddr, PortNumber, IP);		// Settings

	if((hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		throw "Could not create socket.";

	cout << "Attempting to connect the Server: " << inet_ntoa(sockAddr.sin_addr) << endl;

	if(connect(hSocket, (sockaddr*)(&sockAddr), sizeof(sockAddr)) != 0)		// Connect to the server
		throw "Could not connect";

	return true;
}

void WSockClient::StartChat()
{
	sgx_status_t sgx_stat = SGX_SUCCESS;
	sgx_enclave_id_t eid = 0;
	sgx_launch_token_t token ={0};
	int updated = 0;
	char uName[MIN_BUF_LEN], uPassword[MIN_BUF_LEN], uData[MAX_BUF_LEN];
	char buffer[MAX_BUF_LEN] = "Hello World!";
	int choice;
	char Data;

	sgx_stat = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG,&token,&updated,&eid,NULL);

	if (sgx_stat != SGX_SUCCESS) 
	{
		cout<<"App: error %#x, failed to create enclave.\n"<< sgx_stat;
	}

	while(true)
	{	
		cout<<"\n";
		cout<<"\tHARDNING ENDPOINT"<<endl;
		cout<< "1.Encrypt the User Creditional" <<endl;
		cout<< "2.Perform Operation on Server" <<endl;
		cout<< "3.Close the Connection"<<endl;
		cout<< "Choose Your Option : ";
		cin>>choice;
		cout<<endl;

		switch (choice)
		{
		case 1:
			cout<<"PERFORMING ENCRYPTION OPERATION ON CLIENT"<<endl;
			cout<<"\tEnter the User Creditional\n";
			cout<<"USERNAME:";
			cin>>uName;
			cout<<"PASSWORD:";
			cin>>uPassword;

			strcpy(uData,uName);
			strcat(uData,uPassword);
			Encryption(eid, uData);
			cout<<"Data is encrypted successfully"<<endl;
			cout<<"Encrypted Data is: "<<uData<<endl;
			cout<<"Do you want send the Information to Client: ";
			cin>>Data;
			if((Data == 'Y') || (Data == 'y'))
			{
				send(hSocket,uData,sizeof(uData)+1,0);
				cout<<"Encrypted Information Send to Server"<<endl;
			}
			else if((Data == 'N') || (Data == 'n'))
			{
				closesocket(hSocket);
				cout<< "Client Connection was Successfully Terminated"<<endl;
			}
			else
			{
				closesocket(hSocket);
				cout<< "Client Connection was Successfully Terminated"<<endl;
			}
			break;

		case 2:
			cout<<"PERFOMING OPERATION ON SERVER"<<endl;
			cout<<"Information Send to Server:" << buffer<<endl;
			send(hSocket,buffer,sizeof(buffer)+1,0);
			SecretInfo(eid, buffer, MAX_BUF_LEN);
			cout<<"Server Operation Performed Successfully"<<endl;	

			send(hSocket,buffer,sizeof(buffer)+1,0);
			cout<<"Information Received from Server: "<<buffer<<endl;
			break;

		case 3:
			closesocket(hSocket);
			cout<< "Client Connection was Successfully Terminated"<<endl;
			break;

		default:
			break;
		}if((choice == 3)|| (Data == 'N') || (Data == 'n')) {break;}
	}
}