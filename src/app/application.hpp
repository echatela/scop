#pragma once

#include "app/frame_context.hpp"
#include "platform/glfw_context.hpp"
#include "platform/window.hpp"
#include "platform/glad_context.hpp"
#include "app/engine.hpp"

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
	void processInput(FrameContext& frame);
	void updateTime(FrameContext& frame);
};
