#include "Client.h"

int main(int argc, char *argv[])
{
	char StrIP[30];

	try
	{
		WSockClient MyClient(REQ_WINSOCK_VER);	// Winsock startup.

		cout<<"\n##################################################"<<endl;
		cout<<"\tCLIENT INFORMATION"<<endl;
		cout << "\nSERVER IP ADDRESS: ";
		cin.getline(StrIP, 29, '\n');
		cout << "SERVER PORT NUMBER: "<<PORT<<endl;
		
		if(!MyClient.ConnectServer(PORT, StrIP))
		{
			cout << "Client was unable to connect. " << endl;
		}
		cout << "Connected to the Server: " <<StrIP<< endl;
		cout<<"##################################################"<<endl;

		MyClient.StartChat();
	}
	catch(char *ErrMsg) 
	{
		cout << "\nError: " << ErrMsg << endl; 
	}
	return 0;
}