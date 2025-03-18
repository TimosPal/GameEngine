#include "GLFWWindow.h"

#include <Utility/Logger.h>
#include <Input/InputManager.h>

#include <iostream>

namespace Engine {

static void errorCallback(int error, const char* description)
{
	LOG_CRITICAL("Error: {}", std::string(description));
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	KeyState::Type stateType;
	switch (action)
	{
	case GLFW_PRESS:
		stateType = KeyState::Type::Pressed;
		break;
	case GLFW_RELEASE:
		stateType = KeyState::Type::Released;
		break;
	default:
		stateType = KeyState::Type::NotPressed;
		break;
	}

	InputManager::getInstance().onKeyEvent(key, stateType);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	keyCallback(window, button, 0, action, mods);
}

static void scrollCallback(GLFWwindow* window, double xoffset, double yOffset)
{
	InputManager::getInstance().onScrollEvent(yOffset);
}

static void mousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	InputManager::getInstance().onMouseMoveEvent(xPos, yPos);
}

GLFWWindow::GLFWWindow(int width, int height, const std::string& title)
	: IWindow(width, height, title), m_window(nullptr)
{}

bool GLFWWindow::init()
{
	LOG_INFO("Creating window {}", m_title);

	if (!glfwInit()) 
	{
		LOG_CRITICAL("Failed to initialize GLFW!");
		return false;
	}

	glfwSetErrorCallback(errorCallback);
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_window)
	{
		return false;
	}

	glfwSetKeyCallback(m_window, keyCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	glfwSetScrollCallback(m_window, scrollCallback);
	glfwSetCursorPosCallback(m_window, mousePositionCallback);

	m_isActive = true;
	return true;
}

void GLFWWindow::terminate()
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
