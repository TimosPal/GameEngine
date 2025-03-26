#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
class VAO
{
public:
	VAO();
	~VAO();

	void bind();
	void unbind();
private:
	unsigned int m_glVAO;

	bool m_isBound = false;
};

} // Engine

#endif // !VAO_H
