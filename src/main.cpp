#include "app/application.hpp"
#include <exception>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2 || argc > 3)
	{
		std::cerr << "Usage: ./scop <object.obj> [texture.ppm]\n";
		return -1;
	}
	try
	{
		Application app(argv[1],
		                argc == 3 ? argv[2] : "assets/cat.ppm");
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
