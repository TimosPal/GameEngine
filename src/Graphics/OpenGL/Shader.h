#ifndef SHADER_H
#define SHADER_H

#include <Graphics/IShader.h>

namespace Engine {

class Shader : public IShader
{
public:
	Shader();
	Shader(SourceCodeResource* shader, IShader::Type type);
	~Shader();

	bool init() override;
	void destroy() override;

	unsigned int getGLID() const { return m_glShader; }
private:
	unsigned int m_glShader;
};

} // Engine

#endif // !SHADER_H
