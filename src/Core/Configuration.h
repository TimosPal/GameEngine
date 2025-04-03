#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

#if GRAPHICS_API == API_OPENGL
	#include <Graphics/OpenGL/OpenGLRenderer.h>	
	using RendererAPI = Engine::OpenGLRenderer;
#else
	#error Invalid graphics API
#endif

#if WINDOW_LIBRARY == WINDOW_GLFW
	#include <Window/GLFWWindow.h>
	using WindowLib = Engine::GLFWWindow;
#else
	#error Invalid window library
#endif

namespace Engine {

constexpr int default_width = 800;
constexpr int default_height = 600;
constexpr const char* default_title = "MyApp";

struct Configuration
{
	int width = default_width;
	int height = default_height;
	std::string title = default_title;
};

} // Engine

#endif // !CONFIGURATION_H
