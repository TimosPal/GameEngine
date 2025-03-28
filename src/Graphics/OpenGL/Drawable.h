#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "VAO.h"
#include "VBO.h"
#include "Program.h"

namespace Engine {

class Drawable
{
public:
	Drawable(VBO& vbo, Program& program);

	void render();

private:
	VAO m_vao;
	VBO& m_vbo; // Managed by Renderer
	Program& m_program; // Managed by Renderer
};

} // Engine

#endif // !DRAWABLE_H
