#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "app/application.hpp"

Application::Application(const std::string& objPath, const std::string& texPath)
    : _engine(objPath, texPath)
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
	static bool  wasTPressed = false;
	static bool  toggleTexture = false;

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

	if (_window.isKeyPressed(GLFW_KEY_R) == true)
		frame.resetPosition = true;

	if (wasTPressed == true)
	{
		if (_window.isKeyPressed(GLFW_KEY_T) == false)
			wasTPressed = false;
	}
	else if (_window.isKeyPressed(GLFW_KEY_T) == true)
	{
		toggleTexture = !toggleTexture;
		wasTPressed = true;
	}
	frame.toggleTexture = toggleTexture;
}

void Application::updateTime(FrameContext& frame)
{
	static double last = glfwGetTime();
	double        now;

	now = glfwGetTime();
	frame.dt = now - last;
	last = now;
}
