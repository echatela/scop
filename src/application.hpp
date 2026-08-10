#pragma once

#include "context/glfw_context.hpp"
#include "window.hpp"
#include "context/glad_context.hpp"
#include "engine.hpp"

class Application
{
	GlfwContext _glfw;
	Window      _window;
	GladContext _glad;
	Engine      _engine;

public:
	void run();

private:
	void processInput();
};
