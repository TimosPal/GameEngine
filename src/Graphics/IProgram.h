#ifndef IPROGRAM_H
#define IPROGRAM_H

#include "IShader.h"
#include <Resources/Handlers/GenericHandler.h>
#include <Resources/SystemResources/IResource.h>

namespace Engine {

template<typename ShaderDerived>
class IProgram : public IResource
{
public:
	IProgram() : m_isActive(false), m_vert(nullptr), m_frag(nullptr) {};
	IProgram(GenericHandler<ShaderDerived>* vert, GenericHandler<ShaderDerived>* frag) : m_isActive(false), m_vert(vert), m_frag(frag) {};

	virtual void use() = 0;
	virtual void unuse() = 0;

	virtual void setUniform(const std::string& uniformName, float value) = 0;

protected:
	// NOTE: to be used for checking bound usage only, not dereferencing.
	inline static IProgram* programInUse = nullptr;

	bool m_isActive;

	GenericHandler<ShaderDerived>* m_vert;
	GenericHandler<ShaderDerived>* m_frag;
};

} // Engine

#endif // !IPROGRAM_H
