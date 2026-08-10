#include "image_loader.hpp"
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>
#include <vector>

static void skip(std::ifstream& file)
{
	while (true)
	{
		int c = file.peek();
		if (c == EOF)
			throw std::runtime_error("PPM header formatted incorrectly");

		if (c == '#')
		{
			int d;
			do
			{
				file.get();
				d = file.peek();
			} while (d != '\n' && d != EOF);
			continue;
		}

		if (std::isspace(c))
		{
			file.get();
			continue;
		}

		break;
	}
}

Image image_loader::loadImage(const std::string& path)
{
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open())
		throw std::runtime_error("Failed to open image file");

	if (file.get() != 'P' || file.get() != '6')
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
