#include "texture.hpp"
#include "scop_utils/image_loader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

Texture::Texture(const std::string& path)
{
	Image texture = image_loader::loadImage(path);

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0,
	             GL_RGB, GL_UNSIGNED_BYTE, texture.pixels.data());
	glGenerateMipmap(GL_TEXTURE_2D);
}
