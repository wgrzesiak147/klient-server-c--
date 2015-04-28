#include "stdafx.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

char sendbuf[256];
char recvbuf[256];

int _tmain(int argc, _TCHAR* argv[])
{
	long res;
	WSADATA wsaData;
	///////////////////
	res = WSAStartup(MAKEWORD(2, 1), &wsaData);
//	if(res == 0 )
	//	cout << "WSAStartup()\t\t successful" << endl;

	SOCKET slisten, client;

	/////////////
	slisten = socket(AF_INET, SOCK_STREAM, 0);
	//if(slisten != INVALID_SOCKET )
	//	cout << "socket()  \t\t successful" << endl;

	/////////////
	
	sockaddr_in info;		
	info.sin_addr.s_addr = inet_addr("127.0.0.1");
	info.sin_family		 = AF_INET;
	info.sin_port		 = htons(54345);
	int infolen = sizeof(info);
	///////////////
	res = bind(slisten, (struct sockaddr*)&info, infolen);
	//if(res != SOCKET_ERROR )
	//	cout << "bind()  \t\t successful" << endl;


	//////////////// tutaj serwer zaczyna dzia³aæ i s³uchaæ
	while(1)
	{
	memset(&recvbuf, 0, sizeof(recvbuf));
	memset(&sendbuf, 0, sizeof(recvbuf));
	res = listen(slisten, SOMAXCONN);
	if(res != SOCKET_ERROR )
		cout << "listen()  \t\t successful" << endl;


	sockaddr_in clientinfo;
	int clientinfolen = sizeof(clientinfo);

	
		client = accept(slisten, (struct sockaddr*)&clientinfo, &clientinfolen);
		if(client != SOCKET_ERROR)
			cout << "client accepted: " << inet_ntoa(clientinfo.sin_addr) << ":"
			     << ntohs(clientinfo.sin_port) << endl;

		cout<<"send : ";
		cin>>sendbuf;
		res = send(client, sendbuf, strlen(sendbuf), 0);
		
		res = recv(client, recvbuf, 256, 0);
		if(res != SOCKET_ERROR)
		{
			cout << "client : " << recvbuf << endl;
		}
	}

	closesocket(client);
	closesocket(slisten);
	WSACleanup();
	return 0;
}

