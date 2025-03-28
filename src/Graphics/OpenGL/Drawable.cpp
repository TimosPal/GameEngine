#include "Drawable.h"

#include <glad/glad.h>

namespace Engine {

Drawable::Drawable(VBO& vbo, Program& program)
	: m_vbo(vbo), m_program(program)
{
	m_vao.bind();
	m_vbo.setAttributes();
	m_vao.unbind();
}

void Drawable::render()
{
	m_vao.bind();
	m_program.use();

	glDrawArrays(GL_TRIANGLES, 0, m_vbo.getVertCount());
}

} // Engine
