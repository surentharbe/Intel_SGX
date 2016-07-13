#include <iostream>
#include "Server.h"
using namespace std;

#define REQ_WINSOCK_VER 2

int main()
{
	try
	{
		WSockServer MyServer(REQ_WINSOCK_VER);
		if(MyServer.RunServer(4444))
		{
			cout << "Client connected. " << endl;
			MyServer.StartChat();
		}
	}
	catch(char *ErrMsg)
	{
		cout << "\nError: " << ErrMsg;
	}
	return 0;
}
