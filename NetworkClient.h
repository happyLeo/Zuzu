#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <exception>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "12345"
#define DEFAULT_BUFLEN 512

class NetworkClient
{
public:
	NetworkClient();
	~NetworkClient();
	int NetworkClient::Connect();
	int NetworkClient::Send(const char* data);
	int NetworkClient::Shutdown();

private:
	WSADATA wsaData;
	SOCKET ConnectSocket;
	struct addrinfo *result = NULL, *ptr = NULL ,hints;
	int NetworkClient::Initialize();
};
