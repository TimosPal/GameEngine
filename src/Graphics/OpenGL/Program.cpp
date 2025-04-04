#include "Program.h"

#include <glad/glad.h>
#include "GLWrapper.h"

namespace Engine {

Program::Program()
	: IProgram(nullptr, nullptr), m_glProgram(-1)
{
}

Program::Program(GenericHandler<Shader>* vert, GenericHandler<Shader>* frag)
	: IProgram(vert, frag), m_glProgram(-1)
{
}

Program::~Program()
{}

bool Program::init()
{
	m_vert->load();
	m_frag->load();

	GL_RET(glCreateProgram(), m_glProgram);

	unsigned int vertexShader = m_vert->getResource().getGLID();
	unsigned int fragmentShader = m_frag->getResource().getGLID();

	GL(glAttachShader(m_glProgram, vertexShader));
	GL(glAttachShader(m_glProgram, fragmentShader));
	GL(glLinkProgram(m_glProgram));

	int success;
	char infoLog[512];
	GL(glGetProgramiv(m_glProgram, GL_LINK_STATUS, &success));
	if (!success) {
		GL(glGetProgramInfoLog(m_glProgram, 512, NULL, infoLog));
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
	if (!m_isActive)
		return;

	GL(glDeleteProgram(m_glProgram));

	// Shaders are already deleted from the init function.
	if (programInUse == this)
	{
		programInUse = nullptr;
	}
	m_isActive = false;
	m_glProgram = 0;
}

void Program::use()
{
	if (!m_isActive || programInUse == this)
	{
		return;
	}

	programInUse = this;
	GL(glUseProgram(m_glProgram));
}

void Program::unuse()
{
	if (!m_isActive || programInUse != this)
	{
		return;
	}

	programInUse = nullptr;
	GL(glUseProgram(0));
}

int Program::getUniformLocation(const std::string& uniformName)
{
	// Find uniform location from cache if possible
	auto it = m_uniformLocations.find(uniformName);
	int location;
	if (it != m_uniformLocations.end()) {
		location = it->second;
	}
	else {
		GL_RET(glGetUniformLocation(m_glProgram, uniformName.c_str()), location);
		m_uniformLocations[uniformName] = location;
	}

	return location;
}

void Program::setUniform(const std::string& uniformName, float value)
{
	// NOTE: unbinding after use is uneeded overhead, user will most likely use the shader.
	// after a value change.
	use();
	GL(glUniform1f(getUniformLocation(uniformName), value));
}

} // Engine