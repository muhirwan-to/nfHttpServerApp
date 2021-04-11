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
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

#include "Encrypt/base64.h"

/*	There's unresolved symbol on opencv, What I've trying to fix this:
	- Add `Linker -> General -> Additional Library Directories` to `.dll path`
	- Use `opencv` from github and build use cmake.
		-> From cmake, we have vcxproj for each `\modules`
		-> I've trying to add each project (based on #include above)
		-> Another linker error has coming from opencv projects I have added
*/


int main(int argc, char argv[])
{
	crow::SimpleApp app;

	//CROW_ROUTE(app, "/resize_image").methods("GET"_method, "POST"_method)([](const crow::request& req)
	CROW_ROUTE(app, "/").methods("GET"_method, "POST"_method)([](const crow::request& req)
		{
			crow::json::rvalue input = crow::json::load(req.body);

			string	img_str64 = input["input_jpeg"].s();
			string	img_dec64 = decode64(img_str64);
			
			vector<uchar>	img_data(img_dec64.begin(), img_dec64.end());
			cv::Mat			img_mat = cv::imdecode(img_data, cv::IMREAD_UNCHANGED);

			int newWidth = (int)input["desired_width"];
			int newHeight = (int)input["desired_height"];

			cv::resize(img_mat, img_mat, cv::Size(newWidth, newHeight));

			vector<uchar> img_out;
			cv::imencode(".jpg", img_mat, img_out);

			string img_enc64 = encode64(string(img_out.begin(), img_out.end()));

			crow::json::wvalue result;
			result["code"] = 200;
			result["message"] = "success";
			result["output_jpeg"] = img_enc64;

			return crow::response{ std::string(crow::json::dump(result)) };
		});

	app.loglevel(crow::LogLevel::Debug);
	app.port(8080).multithreaded().run();

	return EXIT_SUCCESS;
}