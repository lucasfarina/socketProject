#pragma once
#include "common.h"
#include "importantTypes.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library

int serverSide();

int main() {
	printf("Are you a client(C) or a server(S)?\n");
	
	char c = getchar();
	if (c == 'C' || c == 'c') {
		printf("Client!\n");
	}
	else if (c == 'S' || c == 's') {
		printf("Server!\n");
		serverSide();
	}

	printf("\n\nPress any key to close...");
	getchar(); getchar();
	return 0;
}

int serverSide() {
	//Init Winsocket
	WSADATA wsa;

	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code: %d", WSAGetLastError());
		return 1;
	}
	printf("Initialized.\n");

	//Create socket
	printf("Creating Socket...");
	SOCKET s;
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Couldn't create socket. Error Code: %d", WSAGetLastError());
	}
	printf("SocketCreated.\n");
	return 0;
}