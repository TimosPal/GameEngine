#ifndef VAO_H
#define VAO_H

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
	static VAO* boundVAO;

	unsigned int m_glVAO;
};

} // Engine

#endif // !VAO_H
