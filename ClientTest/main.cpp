
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>

//#pragma comment(lib, "ws2_32.lib")
#pragma comment (lib, "wsock32.lib")


SOCKET handle;
SOCKADDR_IN address; //socket info
WSADATA WsaData; //socket version



//Taken from tutorial at http://www.dreamincode.net/forums/topic/137293-networking-tutorial/
//also https://gafferongames.com/post/sending_and_receiving_packets/

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
	//std::string message = "Hello world!";
	std::string input;

	while (input != "exit")
	{
		std::getline(std::cin, input);

		if (input == "connect")
		{
			Connect("10.15.20.4", 2567);
		}
		else if (input == "exit")
		{
			break;
		}
		else if (input != "")
		{
			MyPacket packet;
			for (int i = 0; i < 256 && i < input.size(); ++i)
			{
				packet.mystring[i] = input[i];
			}
			for (int i = input.size(); i < 256; ++i)
			{
				packet.mystring[i] = 0;
			}
			Send((char*)&packet, sizeof(packet)); //send to all 4 clients
			/*if (packet.mystring)
			{
				printf(packet.mystring);
			}*/
		}

		input = "";
		//MyPacket packet;
		//for (int i = 0; i < message.size(); ++i)
		//{
		//	packet.mystring[i] = message[i];
		//}
		//Send((char*)&packet, sizeof(packet)); //send to all 4 clients

		//Receive((char*)&packet, sizeof(packet)); //send to all 4 clients
	}

	EndSocket();


	return 0;
}


int Connect(char* IP, int Port)
{
	WSAStartup(MAKEWORD(2, 2), &WsaData);

	handle = socket(AF_INET, SOCK_STREAM, 0);
	if (handle == INVALID_SOCKET)
	{
		return 1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(IP);
	address.sin_port = htons(Port);
	int ss = connect(handle, (struct sockaddr*)&address, sizeof(address));
	if (ss != 0)
	{
		printf("Cannot connect\n");
		return 0;
	}

	DWORD nonBlocking = 1;
	if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
	{
		printf("Failed to set non-blocking\n");
		return 0;
	}

	printf("Successfully connected\n");
	return 1;
}

int Send(char* Buf, int len)
{
	int slen = 1;
	slen = send(handle, Buf, len, 0);
	if (slen < 0)
	{
		printf("Did not send data\n");
		return 1;
	}
	return slen;
}

int Receive(char* Buf, int len)
{
	int slen;
	slen = recv(handle, Buf, len, 0);
	if (slen < 0)
	{
		printf("Cannot receive data\n");
		return 1;
	}
	return slen;
}

int EndSocket()
{
	closesocket(handle);
	WSACleanup();
	return 1;
}
