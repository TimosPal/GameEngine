#include "GLFWWindow.h"

#include <GLFW/glfw3.h>

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
	glfwSetErrorCallback(error_callback);
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window)
	{
		// Window or OpenGL context creation failed
		return false;
	}

	return true;
}

} // Engine
