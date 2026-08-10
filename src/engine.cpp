#include "engine.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Engine::Engine(const std::string& objPath, const std::string& texPath)
    : _shader("shaders/vert.glsl", "shaders/frag.glsl"),
      _texture(texPath),
      _mesh(objPath)
{
}

void Engine::update(double dt)
{
	(void)dt;
}

void Engine::render()
{
	glClearColor(0.2f, 0.3f, 0.3, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_texture.bind();

	_shader.use();

	_mesh.draw();
}
