#ifndef PROGRAM_H
#define PROGRAM_H

#include <Graphics/IProgram.h>
#include "Shader.h"

#include <unordered_map>

namespace Engine {

class Program : public IProgram<Shader>
{
public:
	Program();
	Program(InternalHandler<Shader>* vert, InternalHandler<Shader>* frag);
	~Program();

	bool init() override;
	void destroy() override;
	void use() override;
	void unuse() override;

	void setUniform(const std::string& uniformName, float value) override;

private:
	unsigned int m_glProgram;

	std::unordered_map<std::string, int> m_uniformLocations;

	int getUniformLocation(const std::string& uniformName);
};

} // Engine

#endif // !PROGRAM_H
