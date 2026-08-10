#pragma once

struct GLFWwindow;

class Window
{
	GLFWwindow* _window;

public:
	Window();
	~Window();

	bool shouldClose() const;
	void setShouldClose();
	void swapBuffers();
	void pollEvents();

	bool isKeyPressed(int key);

	void setFramebufferSizeCallback();
};
