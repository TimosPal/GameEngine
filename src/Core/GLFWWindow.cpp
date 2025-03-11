#include "GLFWWindow.h"

#include <GLFW/glfw3.h>

#include <iostream>

namespace Engine {

// TODO: refactor
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

GLFWWindow::GLFWWindow(int width, int height, const std::string& title)
	: IWindow(width, height, title)
{}

bool GLFWWindow::Init()
{
	std::cout << "Creating window: " << m_title << std::endl;

	glfwSetErrorCallback(error_callback);
	GLFWwindow* window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!window)
	{
		return false;
	}

	return true;
}

} // Engine
