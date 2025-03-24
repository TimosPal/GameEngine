#ifndef PROGRAM_H
#define PROGRAM_H

#include "Shader.h"

#include <glad/glad.h>

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
class Program
{
public:
	Program(Shader& vert, Shader& frag);
	bool init();
	void destroy();

	unsigned int getGLID() const { return m_glProgram; }

private:
	bool m_isActive;

	Shader m_vert;
	Shader m_frag;

	unsigned int m_glProgram;
};

} // Engine

#endif // !PROGRAM_H
