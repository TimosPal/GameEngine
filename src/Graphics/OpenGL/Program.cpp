#include "Program.h"

#include <glad/glad.h>

namespace Engine {

Program* Program::programInUse = nullptr;

Program::Program(Shader& vert, Shader& frag)
	: m_vert(vert), m_frag(frag), m_isActive(false), m_glProgram(-1)
{
}

Program::~Program()
{
	destroy();
}

bool Program::init()
{
	m_vert.init();
	m_frag.init();

	m_glProgram = glCreateProgram();

	unsigned int vertexShader = m_vert.getGLID();
	unsigned int fragmentShader = m_frag.getGLID();

	glAttachShader(m_glProgram, vertexShader);
	glAttachShader(m_glProgram, fragmentShader);
	glLinkProgram(m_glProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(m_glProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_glProgram, 512, NULL, infoLog);
		LOG_ERROR("LINKING FAILED: {}", infoLog);
		return false;
	}

	m_vert.destroy();
	m_frag.destroy();

	m_isActive = true;

	return true;
}

void Program::destroy()
{
	glDeleteProgram(m_glProgram);

	// Shaders are already deleted from the init function.
	programInUse = nullptr;
	m_isActive = false;
}

void Program::use()
{
	if (programInUse == this)
	{
		return;
	}

	programInUse = this;
	glUseProgram(m_glProgram);
}

void Program::unuse()
{
	if (programInUse != this)
	{
		return;
	}

	programInUse = nullptr;
	glUseProgram(0);
}

} // Engine