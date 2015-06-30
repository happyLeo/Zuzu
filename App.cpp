#include <strsafe.h>
#include <string>
#include <sstream> 
#include <stdlib.h>
#include "stdafx.h"
#include "BodyBasics.h"
#include "NetworkClient.h"

using namespace std;
void mySend(const char* s);

//Sends gesture data to a server
NetworkClient client;

/// <summary>
/// Entry point for the application
/// </summary>
/// <param name="hInstance">handle to the application instance</param>
/// <param name="hPrevInstance">always 0</param>
/// <param name="lpCmdLine">command line arguments</param>
/// <param name="nCmdShow">whether to display minimized, maximized, or normally</param>
/// <returns>status</returns>
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
	)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	client.Connect();
	CBodyBasics application(mySend);
	application.Run(hInstance, nShowCmd);
	client.Shutdown();
}

void mySend(const char* s) {
	std::ostringstream os;
	os << s << "\n";
	client.Send(os.str().c_str());
}
