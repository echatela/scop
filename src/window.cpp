#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

Window::Window()
{
	_window = glfwCreateWindow(800, 600, "Scop", NULL, NULL);
	if (_window == nullptr)
		throw std::runtime_error("Failed to create GLFW window");
	glfwMakeContextCurrent(_window);
}

Window::~Window()
{
	glfwDestroyWindow(_window);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(_window);
}

void Window::setShouldClose()
{
	glfwSetWindowShouldClose(_window, true);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(_window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

bool Window::isKeyPressed(int key)
{
	return glfwGetKey(_window, key) == GLFW_PRESS;
}

void Window::setSizeCallback()
{
	glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
}
