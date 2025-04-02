#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Program.h"

namespace Engine {

class Drawable
{
public:
	Drawable(VBO& vbo, EBO& ebo, Program& program);
	~Drawable();

	void render();

private:
	VAO m_vao;
	VBO& m_vbo;
	EBO& m_ebo;
	Program& m_program;
};

} // Engine

#endif // !DRAWABLE_H
