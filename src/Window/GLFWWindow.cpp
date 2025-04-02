#include "GLFWWindow.h"

#include <Utility/Logger.h>
#include <Input/InputManager.h>

#include <iostream>

#include <Core/Application.h>

#include <Events/WindowResizeEvent.h>
#include <Events/FrameBufferResizeEvent.h>

namespace Engine {

static void errorCallback(int error, const char* description)
{
	LOG_ERROR("errorCode {}: {}", error, std::string(description));
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

static void windowSizeCallback(GLFWwindow* window, int width, int height)
{
	Application::getInstance()->addEvent<WindowResizeEvent>(WindowResizeEvent(width, height));
}

static void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application::getInstance()->addEvent<FrameBufferResizeEvent>(FrameBufferResizeEvent(width, height));
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

	#if GRAPHICS_API == API_OPENGL
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	#endif

	glfwSetErrorCallback(errorCallback);
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_window)
	{
		return false;
	}

	glfwMakeContextCurrent(m_window);

	// Input
	glfwSetKeyCallback(m_window, keyCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	glfwSetScrollCallback(m_window, scrollCallback);
	glfwSetCursorPosCallback(m_window, mousePositionCallback);

	// Window events
	//glfwSetWindowSizeCallback(m_window, windowSizeCallback);
	glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);

	// To be handled for the first init of renderer
	Application::getInstance()->addEvent<FrameBufferResizeEvent>(FrameBufferResizeEvent(m_width, m_height));

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

void GLFWWindow::pollEvents()
{
	glfwPollEvents();
}

bool GLFWWindow::shouldClose()
{
	// TODO: could be handled via callbacks.
	return glfwWindowShouldClose(m_window);
}

void GLFWWindow::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

} // Engine
