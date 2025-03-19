#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <Graphics/IRenderer.h>
#include <glad/glad.h>

#if WINDOW_LIBRARY == WINDOW_GLFW
	#include <GLFW/glfw3.h>
#endif

namespace Engine {

class OpenGLRenderer : public IRenderer
{
public:
	bool init() override
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
private:

};

} // Engine

#endif // !OPENGL_RENDERER_H
