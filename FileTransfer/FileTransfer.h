#ifndef _FILETRANSFER_H_
#define _FILETRANSFER_H_

#ifdef FILETRANSFER_EXPORTS
#define FILETRANSFER_API __declspec(dllexport)
#else
#define FILETRANSFER_API __declspec(dllimport)
#endif

#ifndef _WS2TCPIP_H_
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

FILETRANSFER_API int ReceiveFile(USHORT port);
FILETRANSFER_API int SendFile(PCSTR filename, PCSTR address, USHORT port);
FILETRANSFER_API const char* GetWsaErrorMessage(int code);

#endif