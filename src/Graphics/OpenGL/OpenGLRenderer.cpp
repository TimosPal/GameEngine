#include "OpenGLRenderer.h"

#include <Utility/Logger.h>
#include <Events/FrameBufferResizeEvent.h>
#include <Core/Application.h>

#include <Resources/ResourceManager.h>
#include <Resources/ShaderResource.h>

#include <Graphics/VertexData.h>
#include "Drawable.h"

#include <glad/glad.h>

#if WINDOW_LIBRARY == WINDOW_GLFW
#include <GLFW/glfw3.h>
#endif

#include <random>

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

static float randomFloat(float min, float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

void OpenGLRenderer::submit(const RenderData& data)
{
	m_renderables.push_back(data);
}

void OpenGLRenderer::render()
{
	//auto& vertexResource = ResourceManager<ShaderResource>::getInstance().load("defaultVert", "./assets/shaders/default.vert");
	//auto& fragmentResource = ResourceManager<ShaderResource>::getInstance().load("defaultFrag", "./assets/shaders/default.frag");

	//Shader vertShader(vertexResource, Shader::Type::Vertex);
	//Shader fragShader(fragmentResource, Shader::Type::Fragment);
	//Program prog(vertShader, fragShader);
	//prog.init();

	//std::vector<VertexData<float>::Vertex> data = {
	//	{{ -0.5f, -0.5f}, {0.7f, 0.3f, 0.8f}},
	//	{{  0.5f, -0.5f}, {0.7f, 0.3f, 0.8f}},
	//	{{  0.0f,  0.5f}, {0.7f, 0.3f, 0.8f}}
	//};
	//VertexData vertexData(data);

	//VBO vbo(vertexData, GL_STATIC_DRAW);
	//Drawable obj(vbo, prog);
	//obj.render();

	// Render all renderables
	for (const auto& renderable : m_renderables)
	{
		
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