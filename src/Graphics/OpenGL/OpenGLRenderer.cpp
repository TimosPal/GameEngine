#include "OpenGLRenderer.h"

#include <Utility/Logger.h>
#include <Events/FrameBufferResizeEvent.h>
#include <Core/Application.h>

#include "Drawable.h"
#include <Graphics/Quad2D.h>

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
	int vertOffset = 0;
	for (auto& renderable : m_renderables)
	{
		// TODO: cull renderables that are not visible

		AttributeInfo::AttributeProgramMask mask = 0;
		auto it = m_buffers.find(mask);
		if (it == m_buffers.end()) {
			it = m_buffers.emplace(
				mask,
				std::make_tuple(
					VertexBatch{},
					VBO{ renderable.mesh.getAttributeInfo(), GL_DYNAMIC_DRAW },
					IndexBatch{},
					EBO{ GL_DYNAMIC_DRAW }
				)
			).first;
		}
		auto& [vertexBatch, vbo, indexBatch, ebo] = it->second;

		const auto& newVerts = renderable.mesh.getVertices();
		const auto& newIndices = renderable.mesh.getIndices();

		// Append vertex
		size_t bufferVertOffset = vertexBatch.size();
		vertexBatch.resize(bufferVertOffset + newVerts.size());
		std::memcpy(vertexBatch.data() + bufferVertOffset, newVerts.data(), newVerts.size() * sizeof(float));

		// Append indices
		size_t bufferIndexOffset = indexBatch.size();
		indexBatch.resize(bufferIndexOffset + newIndices.size());
		std::memcpy(indexBatch.data() + bufferIndexOffset, newIndices.data(), newIndices.size() * sizeof(unsigned int));

		// Adjust only the new indices
		for (size_t i = bufferIndexOffset; i < indexBatch.size(); i++)
		{
			indexBatch[i] += vertOffset;
		}
		vertOffset += renderable.mesh.getVertexCount();
	}
	
	// Render all batched buffers.
	for (auto& [_, buffer] : m_buffers)
	{
		m_renderables[0].texture.bind();

		auto& [vertexBatch, vbo, indexBatch, ebo] = buffer;
		vbo.updateData(&vertexBatch);
		ebo.updateData(&indexBatch);

		Drawable obj(vbo, ebo, m_renderables[0].program);
		obj.render();	

		m_renderables[0].texture.unbind();

		vertexBatch.clear();
		indexBatch.clear();
	}

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