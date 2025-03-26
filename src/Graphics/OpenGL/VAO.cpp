#include "VAO.h"

namespace Engine {

VAO::VAO()
{
	glGenVertexArrays(1, &m_glVAO);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_glVAO);
}

void VAO::bind()
{
	if (m_isBound)
		return;

	m_isBound = true;
	glBindVertexArray(m_glVAO);
}

void VAO::unbind()
{
	if (m_isBound)
		return;

	m_isBound = false;
	glBindVertexArray(0);
}

} // Engine