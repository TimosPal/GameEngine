#include "Shader.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Engine {

Shader::Shader()
	: IShader(), m_glShader(-1)
{
}

Shader::Shader(SourceCodeResource* shader, IShader::Type type)
	: IShader(shader, type), m_glShader(-1)
{}

Shader::~Shader()
{
	destroy();
}

bool Shader::init()
{
	auto gl_vertex_type = (m_type == Type::Vertex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
	m_glShader = glCreateShader(gl_vertex_type);

	const char* shaderSourceCodeCString = m_shader->getData().c_str();
	glShaderSource(m_glShader, 1, &shaderSourceCodeCString, NULL);
	glCompileShader(m_glShader);

	int success;
	char infoLog[512];
	glGetShaderiv(m_glShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_glShader, 512, NULL, infoLog);
		LOG_CRITICAL("{} COMPILATION_FAILED: {}", (m_type == Type::Vertex) ? "Vertex" : "Fragment", infoLog);
		return false;
	}

	m_isActive = true;
	return true;
}  

void Shader::destroy()
{
	glDeleteShader(m_glShader);
	m_isActive = false;
}

} // Engine