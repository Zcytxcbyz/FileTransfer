#include "FileTransfer.h"
#include <stdio.h>
#include <direct.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "GetFilename.h"

FILETRANSFER_API int SendFile(PCSTR filename, PCSTR address, USHORT port) {
	FILE* file;
	if (fopen_s(&file, filename, "rb") || file == NULL) {
		WSACleanup();
		return 0;
	}

	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		return -1;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		return -1;
	}

	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, address, (void*)&sockAddr.sin_addr.S_un.S_addr);
	sockAddr.sin_port = htons(port);
	if (connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
		return -1;
	}

	char buffer[MAXBYTE] = { 0 };
	char* fullFilename = GetFilename(filename);
	memcpy(buffer, fullFilename, strlen(fullFilename) + 1);
	free(fullFilename);
	send(sock, buffer, MAXBYTE, 0);
	int count;
	while ((count = fread_s(buffer, MAXBYTE, 1, MAXBYTE, file)) > 0) {
		send(sock, buffer, count, 0);
	}

	shutdown(sock, SD_SEND);
	recv(sock, buffer, MAXBYTE, 0);

	fclose(file);
	closesocket(sock);
	WSACleanup();

	return 0;
}