#include "OpenGLRenderer.h"

#include <Utility/Logger.h>
#include <Events/FrameBufferResizeEvent.h>
#include <Core/Application.h>

#include "Drawable.h"

#include "GLWrapper.h"

#include <iostream>

#if WINDOW_LIBRARY == WINDOW_GLFW
	#include <GLFW/glfw3.h>
#endif

namespace Engine {

static void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	LOG_CRITICAL("Debug message ({}) : {}", id, message);

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

static void frameBufferResize(const FrameBufferResizeEvent& e)
{
	LOG_INFO("Frame buffer size set to {} {}", e.width, e.height);
	GL(glViewport(0, 0, e.width, e.height));
}

bool OpenGLRenderer::init()
{
	#if WINDOW_LIBRARY == WINDOW_GLFW
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("Failed to initialize GLAD");
		return false;
	}
	#endif

	const GLubyte* version = glGetString(GL_VERSION);
	std::string versionString(reinterpret_cast<const char*>(version));
	LOG_INFO("Init glad {}", versionString);

	Application::getInstance()->subscribe<FrameBufferResizeEvent>(frameBufferResize);

	int flags;
	GL(glGetIntegerv(GL_CONTEXT_FLAGS, &flags));
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		LOG_INFO("OpenGL Debug Context Enabled");
	
		GL(glEnable(GL_DEBUG_OUTPUT));
		GL(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
		GL(glDebugMessageCallback(glDebugOutput, nullptr));
		GL(glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
	}
	else {
		LOG_WARNING("OpenGL Debug Context Not Available");
	}

	GL(glEnable(GL_BLEND));  // Enable blending
	GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  // Set blending function for transparency

	return true;
}

void OpenGLRenderer::submit(RenderData&& data)
{
	m_renderables.emplace_back(data);
}

void OpenGLRenderer::render()
{
	if (m_renderables.size() <= 0)
		return;

	// Batch all renderables (Assumes single shader for now)
	std::vector<float> vertexBatch;
	std::vector<unsigned int> indicesBatch;
	int indexOffset = 0;
	for (auto& renderable : m_renderables)
	{
		// Append vertex into batch
		vertexBatch.insert(vertexBatch.end(), renderable.mesh.vertices.begin(), renderable.mesh.vertices.end());

		// Adjust indices to account for existing vertices in batch
		for (unsigned int i : renderable.mesh.indices)
		{
			indicesBatch.push_back(i + indexOffset);
		}
		indexOffset += renderable.mesh.vertices.size();
	}
	
	m_renderables[0].texture.bind();
	int drawingType = GL_DYNAMIC_DRAW;
	static VBO vbo(m_renderables[0].mesh.info, drawingType);
	static EBO ebo(drawingType);

	vbo.updateData(&vertexBatch);
	ebo.updateData(&indicesBatch);

	Drawable obj(vbo, ebo, m_renderables[0].program);

	obj.render();	

	m_renderables[0].texture.unbind();

	m_renderables.clear();
}

void OpenGLRenderer::clear()
{
	// Set the clear color to dark gray
	GL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

	// Clear the color buffer, depth buffer, and stencil buffer (if used)
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

} // Engine