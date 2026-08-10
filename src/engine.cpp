#include "engine.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Engine::Engine() : _shader("shaders/vert.glsl", "shaders/frag.glsl")
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

	_shader.use();
}
