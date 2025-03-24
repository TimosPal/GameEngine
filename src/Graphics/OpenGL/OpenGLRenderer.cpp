#include "OpenGLRenderer.h"

#include <glad/glad.h>
#include <Utility/Logger.h>
#include <Events/FrameBufferResizeEvent.h>
#include <Core/Application.h>

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



	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED: {}", infoLog);
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: {}", infoLog);
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		LOG_ERROR("ERROR::SHADER::LINKING::COMPILATION_FAILED: {}", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VAO
	float vertices[6];
	vertices[0] = randomFloat(-1.0f, 1.0f); // x1
	vertices[1] = randomFloat(-1.0f, 1.0f); // y1

	vertices[2] = randomFloat(-1.0f, 1.0f); // x2
	vertices[3] = randomFloat(-1.0f, 1.0f); // y2

	vertices[4] = randomFloat(-1.0f, 1.0f); // x3
	vertices[5] = randomFloat(-1.0f, 1.0f); // y3

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

} // Engine