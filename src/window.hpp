#pragma once

struct GLFWwindow;

class Window
{
	GLFWwindow* _window;
	float       _width;
	float       _height;

public:
	Window();
	~Window();

	bool shouldClose() const;
	void setShouldClose();
	void getFramebufferSize(int* width, int* height) const;

	void swapBuffers();
	void pollEvents();

	bool isKeyPressed(int key);

	void setFramebufferSizeCallback();
};
