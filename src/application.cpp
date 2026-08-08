#include "application.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Application::run()
{
	_window.setSizeCallback();

	while (_window.shouldClose() != true)
	{
		processInput();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		_window.swapBuffers();
		_window.pollEvents();
	}
}

void Application::processInput()
{
	if (_window.isKeyPressed(GLFW_KEY_ESCAPE) == true)
		_window.setShouldClose();
}
