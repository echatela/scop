// Image loader for scop
#pragma once

#include <string>
#include <vector>

struct Image
{
	std::vector<unsigned char> pixels;
	int                        width;
	int                        height;
};

namespace image_loader
{
Image loadImage(const std::string& path);
}
