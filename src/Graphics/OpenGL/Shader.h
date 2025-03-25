#ifndef SHADER_H
#define SHADER_H

#include <Resources/ShaderResource.h>

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
class Shader
{
public:
	enum class Type {
		Vertex, Fragment
	};

	Shader(ShaderResource& shader, Type type);
	~Shader();

	bool init();
	void destroy();

	unsigned int getGLID() const { return m_glShader; }
private:
	ShaderResource& m_shader;

	bool m_isActive;
	unsigned int m_glShader;
	Type m_type;
};

} // Engine

#endif // !SHADER_H
