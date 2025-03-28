#include "VAO.h"

#include <glad/glad.h>

namespace Engine {

VAO* VAO::boundVAO = nullptr;

VAO::VAO()
{
	glGenVertexArrays(1, &m_glVAO);
}

VAO::~VAO()
{
	boundVAO = nullptr;
	glDeleteVertexArrays(1, &m_glVAO);
}

void VAO::bind()
{
	if (boundVAO == this)
		return;

	boundVAO = this;
	glBindVertexArray(m_glVAO);
}

void VAO::unbind()
{
	if (boundVAO != this)
		return;

	boundVAO = nullptr;
	glBindVertexArray(0);
}

} // Engine