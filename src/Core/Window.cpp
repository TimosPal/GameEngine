#include "Window.h"

#include <iostream>

#include <GLFW/glfw3.h>

namespace Engine {

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

Window::Window()
{
	glfwSetErrorCallback(error_callback);
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window)
	{
		// Window or OpenGL context creation failed
	}
}

Window::~Window() {}


bool Window::Init()
{
	return false;
}

} // Engine