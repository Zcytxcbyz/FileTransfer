#include <stdio.h>
#include <direct.h>
#include "..\FileTransfer\FileTransfer.h"

//ReceiveFile [port]
//ReceiveFile [path] [port]
int main(int argc, char** argv)
{
	short port;
	switch (argc)
	{
	case 1:
		printf("ReceiveFile [port] or ReceiveFile [path] [port]\n");
		return 0;
	case 2:
		port = atoi(argv[1]);
		break;
	case 3:
		if (_chdir(argv[1]) < 0) {
			printf("The path does not exist.\n");
		}
		port = atoi(argv[2]);
		break;
	default:
		printf("Parameter error.\n");
		return -1;
	}
	int err = ReceiveFile(port);
	if (err < 0) {
		int errcode = WSAGetLastError();
		printf("%s %d", GetWsaErrorMessage(errcode), errcode);
	}
	return err;
}



