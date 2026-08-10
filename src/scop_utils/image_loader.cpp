#include "image_loader.hpp"
#include <cctype>
#include <cstddef>
#include <fstream>
#include <ios>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

static void skip(std::ifstream& file)
{
	while (true)
	{
		int c = file.peek();

		if (c == '#')
		{
			int d;
			do
			{
				file.get();
				d = file.peek();
			} while (d != '\n' && d != '\0');
		}

		if (c == '\0' || !std::isspace(c))
			break;

		file.get();
	}
}

Image image_loader::loadImage(const std::string& path)
{
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open())
		throw std::runtime_error("Failed to open image file");

	std::ostringstream oss;
	oss << file.get() << file.get();
	if (oss.str() != "P6")
		throw std::runtime_error("Image format not supported");

	skip(file);
	Image image;

	if (!(file >> image.width))
		throw std::runtime_error("Failed to load image");
	skip(file);
	if (!(file >> image.height))
		throw std::runtime_error("Failed to load image");
	skip(file);
	int maxval;
	if (!(file >> maxval) || maxval != 255)
		throw std::runtime_error("Failed to load image");
	if (!std::isspace(file.get()))
		throw std::runtime_error("Failed to load image");

	image.pixels =
	    std::vector<unsigned char>(size_t(image.width) * image.height * 3);
	file.read(reinterpret_cast<char*>(image.pixels.data()),
	          image.pixels.size());
	if (file.gcount() != static_cast<std::streamsize>(image.pixels.size()))
		throw std::runtime_error("Truncated PPM data");

	return image;
}
