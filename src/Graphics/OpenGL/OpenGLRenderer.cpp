#include "OpenGLRenderer.h"

#include <glad/glad.h>
#include <Utility/Logger.h>
#include <Events/FrameBufferResizeEvent.h>
#include <Core/Application.h>
#include "Shader.h"
#include "Program.h"
#include "VBO.h"
#include "VAO.h"

#include <Resources/ResourceManager.h>
#include <Resources/ShaderResource.h>

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

void OpenGLRenderer::clear()
{
	// Set the clear color to dark gray
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Clear the color buffer, depth buffer, and stencil buffer (if used)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	// TEMP
	auto& vertexResource = ResourceManager<ShaderResource>::getInstance().load("defaultVert", "./assets/shaders/default.vert");
	const char* vertexShaderSource = vertexResource.getString().c_str();

	auto& fragmentResource = ResourceManager<ShaderResource>::getInstance().load("defaultFrag", "./assets/shaders/default.frag");
	const char* fragmentShaderSource = fragmentResource.getString().c_str();

	Shader vertShader(vertexResource, Shader::Type::Vertex);
	vertShader.init();
	Shader fragShader(fragmentResource, Shader::Type::Fragment);
	fragShader.init();

	Program prog(vertShader, fragShader);
	prog.init();

	std::vector<float> vertices(6);
	vertices[0] = randomFloat(-1.0f, 1.0f); // x1
	vertices[1] = randomFloat(-1.0f, 1.0f); // y1
	
	vertices[2] = randomFloat(-1.0f, 1.0f); // x2
	vertices[3] = randomFloat(-1.0f, 1.0f); // y2
	
	vertices[4] = randomFloat(-1.0f, 1.0f); // x3
	vertices[5] = randomFloat(-1.0f, 1.0f); // y3
	
	VAO vao;
	vao.bind();

	VBO<float> vbo(vertices, 0, 2);
	vbo.init();
	
	prog.use();
	glDrawArrays(GL_TRIANGLES, 0, vbo.getVertCount());
}

} // Engine