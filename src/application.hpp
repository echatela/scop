#pragma once

#include "context/glfw_context.hpp"
#include "window.hpp"
#include "context/glad_context.hpp"

class Application
{
	GlfwContext _glfw;
	Window      _window;
	GladContext _glad;

public:
	void run();

private:
	void processInput();
};
