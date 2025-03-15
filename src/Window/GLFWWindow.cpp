#include "GLFWWindow.h"

#include <Utility/Logger.h>

#include <iostream>

namespace Engine {

static void error_callback(int error, const char* description)
{
	LOG_CRITICAL("Error: {}", std::string(description));
}

GLFWWindow::GLFWWindow(int width, int height, const std::string& title)
	: IWindow(width, height, title), m_window(nullptr)
{}

bool GLFWWindow::Init()
{
	LOG_INFO("Creating window {}", m_title);

	if (!glfwInit()) 
	{
		LOG_CRITICAL("Failed to initialize GLFW!");
		return false;
	}

	glfwSetErrorCallback(error_callback);
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_window)
	{
		return false;
	}

	m_isActive = true;
	return true;
}

void GLFWWindow::Terminate()
{
	LOG_INFO("Closing window {}", m_title);
	glfwDestroyWindow(m_window);
	glfwTerminate();

	m_isActive = false;
}

void GLFWWindow::PollEvents()
{
	glfwPollEvents();
}

bool GLFWWindow::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

} // Engine
