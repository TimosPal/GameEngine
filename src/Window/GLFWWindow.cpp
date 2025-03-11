#include "GLFWWindow.h"

#include <iostream>

namespace Engine {

// TODO: refactor
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

GLFWWindow::GLFWWindow(int width, int height, const std::string& title)
	: IWindow(width, height, title), m_window(nullptr)
{}

bool GLFWWindow::Init()
{
	std::cout << "Creating window: " << m_title << std::endl;

	if (!glfwInit()) 
	{
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return false;
	}

	glfwSetErrorCallback(error_callback);
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_window)
	{
		return false;
	}

	return true;
}

void GLFWWindow::Terminate()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

} // Engine
