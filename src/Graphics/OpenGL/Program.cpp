#include "Program.h"

#include <glad/glad.h>

namespace Engine {

Program::Program()
	: IProgram(nullptr, nullptr), m_glProgram(-1)
{
}

Program::Program(InternalResource<Shader>* vert, InternalResource<Shader>* frag)
	: IProgram(vert, frag), m_glProgram(-1)
{
}

Program::~Program()
{
	destroy();
}

bool Program::init()
{
	m_vert->load();
	m_frag->load();

	m_glProgram = glCreateProgram();

	unsigned int vertexShader = m_vert->getInternalObject().getGLID();
	unsigned int fragmentShader = m_frag->getInternalObject().getGLID();

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

	m_vert->unload();
	m_frag->unload();

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