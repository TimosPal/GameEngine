#include "OpenGLRenderer.h"

#include <glad/glad.h>
#include <Utility/Logger.h>

#if WINDOW_LIBRARY == WINDOW_GLFW
#include <GLFW/glfw3.h>
#endif

namespace Engine {

bool OpenGLRenderer::init()
{
	LOG_INFO("Initializing OpenGL");

	#if WINDOW_LIBRARY == WINDOW_GLFW
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("Failed to initialize GLAD");
		return false;
	}
	#endif

	return true;
}

void OpenGLRenderer::clear()
{
	// Set the clear color to dark gray
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Clear the color buffer, depth buffer, and stencil buffer (if used)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

} // Engine