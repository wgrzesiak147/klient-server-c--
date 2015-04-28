// ConsoleApplication6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
#define myport 3000
using namespace std;

WSADATA wsa;
SOCKADDR_IN  serverinfo;
SOCKET socket1;


char* sendbuf;
char* recvbuf;
int _tmain(int argc, _TCHAR* argv[])
{
	long rc;
	WSADATA wsaData;
	SOCKET sConnect;
	sockaddr_in conpar;
	cout<<"Waiting for server response..."<<endl;

		while(1)
		{

		rc = WSAStartup(MAKEWORD(2, 0), &wsaData);
	
		sConnect = socket(AF_INET, SOCK_STREAM, 0);
		conpar.sin_addr.s_addr = inet_addr("127.0.0.1");
		conpar.sin_family      = AF_INET;
		conpar.sin_port        = htons(54345);
		int conparlen = sizeof(conpar);
		////////Conect();
		rc = connect(sConnect, (struct sockaddr*)&conpar, conparlen);
		
		if(rc != SOCKET_ERROR)
			{
				cout<<"Connected"<<endl;
			memset(&sendbuf, 0, sizeof(sendbuf));
			memset(&recvbuf, 0, sizeof(recvbuf));
			//////////recv() odbieranie wiadomoœci;
			rc = recv(sConnect, recvbuf, strlen(recvbuf), 0);
			cout<<"dostalem"<<endl;
				if(rc != SOCKET_ERROR)
					{
					cout <<"Server: "<< recvbuf << endl;
					}
			cout << "Send: ";
			cin>>sendbuf;
			//////////send() wysy³anie wiadomoœci;
			rc = send(sConnect, sendbuf, strlen(sendbuf), 0);
			}
		}

	closesocket(sConnect);
	WSACleanup();
	return 0;
}

