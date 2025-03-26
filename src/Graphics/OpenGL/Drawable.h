#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "VAO.h"
#include "VBO.h"
#include "Program.h"

namespace Engine {

class Drawable
{
public:
private:
	VAO m_vao;
	VBO m_vbo;
	Program& m_program;
};

} // Engine

#endif // !DRAWABLE_H
