#include "VAO.h"

namespace Engine {

VAO::VAO()
{
	glGenVertexArrays(1, &m_glVAO);
}

VAO::~VAO()
{
	glDeleteBuffers(1, &m_glVAO);
}

void VAO::bind()
{
	// TODO: save previous bind state?
	glBindVertexArray(m_glVAO);
}

} // Engine