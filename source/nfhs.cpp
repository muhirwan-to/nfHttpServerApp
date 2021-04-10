// NFHS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include "pch.h"

int main(const std::vector<std::string>& args)
{
	//Port to listen
	Poco::UInt16 port = 9999;

	Poco::Net::ServerSocket socket(port);

	Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams();
	//Sets the maximum number of queued connections.
	pParams->setMaxQueued(100);
	//Sets the maximum number of simultaneous threads available for this Server
	pParams->setMaxThreads(16);
	// Instanciate HandlerFactory
	Poco::Net::HTTPServer server(new HandlerFactory(), socket, pParams);

	server.start();

	waitForTerminationRequest();

	server.stop();

	return EXIT_OK;
}