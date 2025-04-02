#include "VAO.h"

#include <glad/glad.h>
#include "GLWrapper.h"

namespace Engine {

VAO* VAO::boundVAO = nullptr;

VAO::VAO()
{
	GL(glGenVertexArrays(1, &m_glVAO));
}

VAO::~VAO()
{
	if (boundVAO == this)
		boundVAO = nullptr;
	GL(glDeleteVertexArrays(1, &m_glVAO));
}

void VAO::bind()
{
	if (boundVAO == this)
		return;

	boundVAO = this;
	GL(glBindVertexArray(m_glVAO));
}

void VAO::unbind()
{
	if (boundVAO != this)
		return;

	boundVAO = nullptr;
	GL(glBindVertexArray(0));
}

} // Engine