#pragma once
#include "common.h"
#include "importantTypes.h"
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int serverSide();

int main() {
	printf("Are you a client(C) or a server(S)?\n");
	int r = 0;
	char c = getchar();
	if (c == 'C' || c == 'c') {
		printf("\nClient!\n");
	}
	else if (c == 'S' || c == 's') {
		printf("\nServer!\n");
		r = serverSide();
	}

	printf("\n\nPress any key to close...");
	getchar(); getchar();
	return r;
}

int serverSide() {
	//Init Winsocket----------------------------------
	WSADATA wsa;

	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code: %d", WSAGetLastError());
		return 1;
	}
	printf(" Initialized.\n");

	//Resolve server address and port------------------------------
	struct addrinfo *result = NULL;
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	printf("Resolving server address and port...");
	if (getaddrinfo(NULL, DEFAULT_PORT, &hints, &result) != 0) {
		printf("Couldn't resolve server address and/or port. Error Code: %d", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	printf(" Server address and port resolved.\n");

	//Create socket--------------------------------------------------
	printf("Creating Socket...");
	SOCKET s;
	if ((s = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == INVALID_SOCKET) {
		printf("Couldn't create socket. Error Code: %d", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	printf(" Socket Created.\n");

	//Setup socket for TCP listening
	printf("\nSetting up socket for listening...");
	if (bind(s, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
		printf("Couldn't setup socket for listening. Error Code: %d", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(s);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result);
	printf(" Socket setup for listening.\n");

	//Start listening
	printf("\nStarting listening...");
	if (listen(s, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listening Failed. Error Code: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 1;
	}
	printf("\nListening...\n");

	//Try accept a client
	SOCKET clientSocket;
	clientSocket = accept(s, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		printf("Client accept failed. Error Code: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 1;
	}
	printf(" Client Accepted\n");
	//No longer need server socket, if you wanted to keep accepting do not close it
	closesocket(s);

	return 0;
}