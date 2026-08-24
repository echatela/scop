#include "application.hpp"
#include <exception>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		std::cerr << "Usage: ./scop <file.obj>\n";
		return -1;
	}
	try
	{
		Application app(argc == 2 ? argv[1] : "assets/42.obj");
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
