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

		_window.getFramebufferSize(&frame.width, &frame.height);
		processInput(frame);
		updateTime(frame);

		_engine.update(frame);
		_engine.render();

		_window.swapBuffers();
		_window.pollEvents();
	}
}

void Application::processInput(FrameContext& frame)
{
	static bool wasTPressed = false;
	static bool toggleTexture = false;
	static bool wasRPressed = false;
	static bool toggleRotation = false;

	if (_window.isKeyPressed(GLFW_KEY_ESCAPE) == true)
		_window.setShouldClose();

	if (_window.isKeyPressed(GLFW_KEY_E) == true)
		frame.rotationY++;
	if (_window.isKeyPressed(GLFW_KEY_Q) == true)
		frame.rotationY--;

	if (_window.isKeyPressed(GLFW_KEY_W) == true)
		frame.moveZ--;
	if (_window.isKeyPressed(GLFW_KEY_S) == true)
		frame.moveZ++;
	if (_window.isKeyPressed(GLFW_KEY_A) == true)
		frame.moveX--;
	if (_window.isKeyPressed(GLFW_KEY_D) == true)
		frame.moveX++;
	if (_window.isKeyPressed(GLFW_KEY_LEFT_SHIFT) == true)
		frame.moveY--;
	if (_window.isKeyPressed(GLFW_KEY_SPACE) == true)
		frame.moveY++;

	frame.zoom = _window.consumeScroll();

	if (_window.isKeyPressed(GLFW_KEY_R) == true)
		frame.rotate = true;

	if (wasRPressed == true)
	{
		if (_window.isKeyPressed(GLFW_KEY_R) == false)
			wasRPressed = false;
	}
	else if (_window.isKeyPressed(GLFW_KEY_R) == true)
	{
		toggleRotation = !toggleRotation;
		wasRPressed = true;
	}
	frame.rotate = toggleRotation;

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
