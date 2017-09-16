
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")


SOCKET sock; //the socket to be used
SOCKET sock2[200]; //the sockets received from and sent to Clients

SOCKADDR_IN i_sock2; //info about connected clients

SOCKADDR_IN i_sock; //info about socket
WSADATA Data; //socket version
int clients = 0;



//Taken from tutorial at http://www.dreamincode.net/forums/topic/137293-networking-tutorial/


struct MyPacket
{
	int mylong;
	char mystring[256];
};



int StartServer(int Port);
int Send(char* Buf, int len, int Client);
int Receive(char* Buf, int len, int Client);
int EndSocket();




int main()
{
	for (int i = 0; i < 4; ++i)
	{
		MyPacket packet;
		Send((char*)&packet, sizeof(packet), i); //send to all 4 clients
	}

	for (int i = 0; i < 4; ++i)
	{
		MyPacket packet;
		Receive((char*)&packet, sizeof(packet), i); //send to all 4 clients
	}

	return 0;
}

int StartServer(int Port)
{
	int err;
	WSAStartup(MAKEWORD(2, 2), &Data); //init socket & set version
	sock = socket(AF_INET, SOCK_STREAM, 0); //0 means UDP by default
	if (sock == INVALID_SOCKET)
	{
		Sleep(4000);
		exit(0);
		return 0;
	}

	i_sock.sin_family = AF_INET;
	i_sock.sin_addr.s_addr = htonl(INADDR_ANY); //start server at my IP
	i_sock.sin_port = htons(Port);
	err = bind(sock, (LPSOCKADDR)&i_sock, sizeof(i_sock)); //associate local address with socket
	if (err != 0)
	{
		return 0;
	}

	err = listen(sock, 2); //2 is max number of clients supported
	if (err == SOCKET_ERROR)
	{
		return 0;
	}

	while (true)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (clients < 4)
			{
				int so2len = sizeof(i_sock2);
				sock2[clients] = accept(sock, (sockaddr*)&i_sock2, &so2len);
				if (sock2[clients] == INVALID_SOCKET)
				{
					return 0;
				}
				printf("a client has joined the server(IP: %s)\n", i_sock2.sin_addr.s_addr);
				++clients;
				continue;
			}
			else
			{
				break;
			}
		}
	}

	return 1;
}

int Send(char* Buf, int len, int Client)
{
	int slen = send(sock2[Client], Buf, len, 0);
	if (slen < 0)
	{
		printf("Cannot send data!\n");
		return 1;
	}
	return slen;
}

int Receive(char* Buf, int len, int Client)
{
	int slen = recv(sock2[Client], Buf, len, 0);
	if (slen < 0)
	{
		printf("Cannot receive data!\n");
		return 1;
	}
	return slen;
}

int EndSocket()
{
	closesocket(sock);
	WSACleanup();
	return 1;
}
