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
#include "crow.h"
#include "crow/utility.h"

int main(const std::vector<std::string>& args)
{
	/*	crow\examples
		some of the example using `crow::SimpleApp`.
		but when Debug, the breakpoint inside lambda function is never invoked. I don't know what's wrong there,
		either my PC's connection port, proxy, or something I don't know
	*/

	crow::SimpleApp app;

	CROW_ROUTE(app, "/resize_image").methods("POST"_method)([](const crow::request& req)
		{
			/*	this lambda body is never called. This log is only have in every build.
				I've getting stuck and didn't get any solution yet
				---
				(2021-04-10 08:51:18) [INFO    ] Crow/0.1 server is running at 0.0.0.0:8080 using 6 threads
				(2021-04-10 08:51:18) [INFO    ] Call `app.loglevel(crow::LogLevel::Warning)` to hide Info level logs.
			*/

			crow::json::rvalue rres = crow::json::load(req.body);
			crow::json::wvalue wres;

			// to do : resize image using opencv

			wres["code"] = 200;
			wres["message"] = "success";

			ostringstream os;
			os << crow::json::dump(wres);
			return crow::response{ os.str() };
		});

	app.port(8080).multithreaded().run();

	return EXIT_SUCCESS;
}