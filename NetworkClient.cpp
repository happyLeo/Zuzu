#include "NetworkClient.h"

/* Creates an initialized NetworkClient instance*/
NetworkClient::NetworkClient()
{
	ConnectSocket = INVALID_SOCKET;
	int iRes;
	if ((iRes = Initialize()) == 1) {
		printf("Error: Failed to initialize.");
		exit;
	}
}

NetworkClient::~NetworkClient(){}

/* Sets the ground for connection.
 * Returns 0 for success, 1 for failure.
 */
int NetworkClient::Initialize() {
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	return 0;
}

int NetworkClient::Connect() {
	// Connect to server.
	int iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	return 0;
}

int NetworkClient::Send(const char* data)
{	
	// Send an initial buffer
	int iResult = send(ConnectSocket, data, (int)strlen(data), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	//OutputDebugStringW(L"Send ");
	return 0;
}

//shutdown socket for both send and recieve
int NetworkClient::Shutdown() {
	OutputDebugStringW(L"\nClient: Shutting down connection\n");
	int iResult = shutdown(ConnectSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	return 0;
}
