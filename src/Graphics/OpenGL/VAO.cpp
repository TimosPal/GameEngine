#include "VAO.h"

namespace Engine {

VAO* VAO::m_boundVAO = nullptr;

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
	if (m_boundVAO == this)
		return;

	glBindVertexArray(m_glVAO);
}

void VAO::unbind()
{
	if (m_boundVAO != this)
		return;

	glBindVertexArray(0);
}

} // Engine