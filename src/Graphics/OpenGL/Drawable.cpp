#include "Drawable.h"

#include "GLWrapper.h"

#include <Utility/Logger.h>

namespace Engine {

Drawable::Drawable(VBO& vbo, EBO& ebo, Program& program)
	: m_vbo(vbo), m_ebo(ebo), m_program(program)
{
	m_vao.bind();
	m_ebo.bind();
	m_vbo.bind();
	m_vbo.setAttributes();
	m_vao.unbind(); 
}

Drawable::~Drawable()
{
	m_vao.bind();
	m_ebo.unbind();
	m_vbo.unbind();
	m_vao.unbind();
}

void Drawable::render()
{
	m_vao.bind();
	m_program.use();

	GL(glDrawElements(GL_TRIANGLES, m_ebo.getIndicesCount(), GL_UNSIGNED_INT, 0));

	m_vao.unbind();
}

} // Engine
