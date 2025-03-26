#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "VAO.h"
#include "VBO.h"
#include "Program.h"

namespace Engine {

template<typename T>
class Drawable
{
public:
	Drawable(VBO<T>& vbo, Program& program)
		: m_vbo(vbo), m_program(program)
	{
		m_vao.bind();
		m_vbo.setAttributes();
		m_vao.unbind();
	}

	void render()
	{
		m_vao.bind();
		m_program.use();

		glDrawArrays(GL_TRIANGLES, 0, m_vbo.getVertCount());
	}

private:
	VAO m_vao;
	VBO<T>& m_vbo; // Managed by Renderer
	Program& m_program; // Managed by Renderer
};

} // Engine

#endif // !DRAWABLE_H
