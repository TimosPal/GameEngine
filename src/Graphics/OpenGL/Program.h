#ifndef PROGRAM_H
#define PROGRAM_H

#include <Graphics/IProgram.h>
#include "Shader.h"

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
class Program : public IProgram<Shader>
{
public:
	Program();
	Program(InternalResource<Shader>* vert, InternalResource<Shader>* frag);
	~Program();

	bool init();
	void destroy();
	void use();
	void unuse();

private:
	unsigned int m_glProgram;
};

} // Engine

#endif // !PROGRAM_H
