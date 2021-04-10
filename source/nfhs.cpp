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
	crow::SimpleApp app;

	CROW_ROUTE(app, "/resize_image").methods("POST"_method)([](const crow::request& req)
		{
			crow::json::rvalue rres = crow::json::load(req.body);
			crow::json::wvalue wres;

			// to do

			wres["code"] = 200;
			wres["message"] = "success";

			ostringstream os;
			os << crow::json::dump(wres);
			return crow::response{ os.str() };
		});

	app.port(8080).multithreaded().run();

	return EXIT_SUCCESS;
}