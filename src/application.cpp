#include "application.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application::Application(const std::string& objPath)
    : _engine(objPath)
{
}

void Application::run()
{
	double last = glfwGetTime();
	while (_window.shouldClose() != true)
	{
		processInput();

		double now = glfwGetTime();
		double dt = now - last;
		last = now;
		int width, height;
		_window.getFramebufferSize(&width, &height);
		_engine.update(dt, width, height);
		_engine.render();

		_window.swapBuffers();
		_window.pollEvents();
	}
}

void Application::processInput()
{
	if (_window.isKeyPressed(GLFW_KEY_ESCAPE) == true)
		_window.setShouldClose();
}
