#include "application.hpp"
#include "frame_context.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application::Application(const std::string& objPath)
    : _engine(objPath)
{
}

void Application::run()
{
	while (_window.shouldClose() != true)
	{
		FrameContext frame;

		processInput(frame);
		_window.getFramebufferSize(&frame.width, &frame.height);
		updateTime(frame);

		_engine.update(frame);
		_engine.render();

		_window.swapBuffers();
		_window.pollEvents();
	}
}

void Application::processInput(FrameContext& frame)
{
//	bool wasTPressed = false;
	bool wasRPressed = false;

	if (_window.isKeyPressed(GLFW_KEY_ESCAPE) == true)
		_window.setShouldClose();

	if (_window.isKeyPressed(GLFW_KEY_W) == true)
		frame.rotationX--;
	if (_window.isKeyPressed(GLFW_KEY_S) == true)
		frame.rotationX++;
	if (_window.isKeyPressed(GLFW_KEY_A) == true)
		frame.rotationY--;
	if (_window.isKeyPressed(GLFW_KEY_D) == true)
		frame.rotationY++;
	if (_window.isKeyPressed(GLFW_KEY_Q) == true)
		frame.rotationZ--;
	if (_window.isKeyPressed(GLFW_KEY_E) == true)
		frame.rotationZ++;

	frame.zoom = _window.consumeScroll();

	if (_window.isKeyPressed(GLFW_KEY_R) == true && wasRPressed == false)
		frame.resetPosition = true;
}

void Application::updateTime(FrameContext& frame)
{
	static double last = glfwGetTime();
	double now;

	now = glfwGetTime();
	frame.dt = now - last;
	last = now;
}
