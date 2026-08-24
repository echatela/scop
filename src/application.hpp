#pragma once

#include "context/glfw_context.hpp"
#include "window.hpp"
#include "context/glad_context.hpp"
#include "engine.hpp"
#include <string>

class Application
{
	GlfwContext _glfw;
	Window      _window;
	GladContext _glad;
	Engine      _engine;

public:
	Application(const std::string& objPath);

	void run();

private:
	void processInput();
};
