#include "GLFWWindow.h"

#include <Utility/Logger.h>

#include <iostream>

namespace Engine {

void error_callback(int error, const char* description)
{
	Logger::log_critical("Error: " + std::string(description));
}

GLFWWindow::GLFWWindow(int width, int height, const std::string& title)
	: IWindow(width, height, title), m_window(nullptr)
{}

bool GLFWWindow::Init()
{
	Logger::set_default_pattern();

	Logger::log_info("Creating window " + m_title);

	if (!glfwInit()) 
	{
		Logger::log_critical("Failed to initialize GLFW!");
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
	Logger::log_info("Closing window " + m_title);
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

} // Engine
