#include <stdio.h>
#include "..\FileTransfer\FileTransfer.h"

//SendFile [file] [address] [port]
int main(int argc, char** argv)
{
	short port;
	char* filename, * address;
	switch (argc) {
	case 1:
		printf("SendFile [file] [address] [port]\n");
		return 0;
	case 4:
		filename = argv[1];
		address = argv[2];
		port = atoi(argv[3]);
		break;
	default:
		printf("Parameter error.\n");
		return -1;
	}
	int err = SendFile(filename, address, port);
	if (err < 0) {
		int errcode = WSAGetLastError();
		printf("%s %d", GetWsaErrorMessage(errcode), errcode);
	}
	return err;
}



