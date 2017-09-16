
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")


SOCKET sock;
SOCKADDR_IN i_sock; //socket info
WSADATA Data; //socket version


struct MyPacket
{
	int mylong;
	char mystring[256];
};


int Connect(char* IP, int Port);
int Send(char* Buf, int len);
int Receive(char* Buf, int len);
int EndSocket();




int main()
{
	while (true)
	{
		MyPacket packet;
		Send((char*)&packet, sizeof(packet)); //send to all 4 clients

		Receive((char*)&packet, sizeof(packet)); //send to all 4 clients
	}


	return 0;
}


int Connect(char* IP, int Port)
{
	WSAStartup(MAKEWORD(2, 2), &Data);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		return 1;
	}

	i_sock.sin_family = AF_INET;
	i_sock.sin_addr.s_addr = inet_addr(IP);
	i_sock.sin_port = htons(Port);
	int ss = connect(sock, (struct sockaddr*)&i_sock, sizeof(i_sock));
	if (ss != 0)
	{
		printf("Cannot connect\n");
		return 0;
	}

	printf("Successfully connected\n");
	return 1;
}

int Send(char* Buf, int len)
{
	int slen;
	slen = send(sock, Buf, len, 0);
	if (slen < 0)
	{
		printf("Cannot send data\n");
		return 1;
	}
	return slen;
}

int Receive(char* Buf, int len)
{
	int slen;
	slen = recv(sock, Buf, len, 0);
	if (slen < 0)
	{
		printf("Cannot receive data\n");
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
