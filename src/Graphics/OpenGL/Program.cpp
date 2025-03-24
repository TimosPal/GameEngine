#include "Program.h"

namespace Engine {

Program::Program(Shader& vert, Shader& frag)
	: m_vert(vert), m_frag(frag), m_isActive(false)
{
}

bool Program::init()
{
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
	// Not sure how and if programs are deletable.
	m_isActive = false;
}

} // Engine