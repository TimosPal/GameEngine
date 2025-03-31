#include "OpenGLRenderer.h"

#include <Utility/Logger.h>
#include <Events/FrameBufferResizeEvent.h>
#include <Core/Application.h>

#include <Graphics/VertexData.h>
#include "Drawable.h"

#include <glad/glad.h>

#if WINDOW_LIBRARY == WINDOW_GLFW
#include <GLFW/glfw3.h>
#endif

namespace Engine {

static void frameBufferResize(const FrameBufferResizeEvent& e)
{
	LOG_INFO("Frame buffer size set to {} {}", e.width, e.height);
	glViewport(0, 0, e.width, e.height);
}

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

	Application::getInstance()->subscribe<FrameBufferResizeEvent>(frameBufferResize);

	return true;
}

void OpenGLRenderer::submit(const RenderData& data)
{
	m_renderables.push_back(data);
}

void OpenGLRenderer::render()
{
	// Render all renderables
	for (const auto& renderable : m_renderables)
	{
		VertexData vertexData(renderable.vertexData);

		VBO vbo(vertexData, GL_STATIC_DRAW);
		Drawable obj(vbo, renderable.program);
		obj.render();		
	}

	m_renderables.clear();
}

void OpenGLRenderer::clear()
{
	// Set the clear color to dark gray
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Clear the color buffer, depth buffer, and stencil buffer (if used)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

} // Engine