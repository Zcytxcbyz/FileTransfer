#include "FileTransfer.h"
#include <stdio.h>
#include <direct.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

FILETRANSFER_API int ReceiveFile(USHORT port) {
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		return -1;
	}

	SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock == INVALID_SOCKET) {
		return -1;
	}

	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockAddr.sin_port = htons(port);
	if (bind(servSock, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
		return -1;
	}

	listen(servSock, 20);

	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

	char buffer[MAXBYTE] = { 0 };
	recv(clntSock, buffer, MAXBYTE, 0);
	char filename[MAXBYTE] = { 0 };
	memcpy(filename, buffer, strlen(buffer) + 1);
	FILE* file;
	if (fopen_s(&file, filename, "wb") || file == NULL) {
		closesocket(clntSock);
		closesocket(servSock);
		WSACleanup();
		return 0;
	}
	int count;
	while ((count = recv(clntSock, buffer, MAXBYTE, 0)) > 0)
	{
		fwrite(buffer, count, 1, file);
	}

	fclose(file);
	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();
    return 0;
}