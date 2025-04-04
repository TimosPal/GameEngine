#include "Shader.h"

#include <glad/glad.h>
#include "GLWrapper.h"

namespace Engine {

Shader::Shader()
	: IShader(), m_glShader(-1)
{
}

Shader::Shader(GenericHandler<SourceResource>* shader, IShader::Type type)
	: IShader(shader, type), m_glShader(-1)
{}

Shader::~Shader()
{}

bool Shader::init()
{
	auto gl_vertex_type = (m_type == Type::Vertex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
	GL_RET(glCreateShader(gl_vertex_type), m_glShader);

	m_shader->load();
	const char* shaderSourceCodeCString = m_shader->getResource().getData().c_str();
	GL(glShaderSource(m_glShader, 1, &shaderSourceCodeCString, NULL));
	GL(glCompileShader(m_glShader));

	int success;
	char infoLog[512];
	GL(glGetShaderiv(m_glShader, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GL(glGetShaderInfoLog(m_glShader, 512, NULL, infoLog));
		LOG_CRITICAL("{} COMPILATION_FAILED: {}", (m_type == Type::Vertex) ? "Vertex" : "Fragment", infoLog);
		return false;
	}

	m_isActive = true;
	return true;
}  

void Shader::destroy()
{
	if (!m_isActive)
		return;

	GL(glDeleteShader(m_glShader));
	m_isActive = false;
	m_glShader = 0;
}

} // Engine