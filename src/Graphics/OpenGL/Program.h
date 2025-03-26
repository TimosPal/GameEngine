#ifndef PROGRAM_H
#define PROGRAM_H

#include "Shader.h"

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
class Program
{
public:
	Program(Shader& vert, Shader& frag);
	~Program();

	bool init();
	void use();
	void unuse();

private:
	static Program* programInUse;

	bool m_isActive = false;

	Shader m_vert;
	Shader m_frag;

	unsigned int m_glProgram;
	
	void destroy();
};

} // Engine

#endif // !PROGRAM_H
