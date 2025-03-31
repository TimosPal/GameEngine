#ifndef IPROGRAM_H
#define IPROGRAM_H

#include "IShader.h"
#include <Resources/InternalResource.h>

namespace Engine {

template<typename ShaderDerived>
class IProgram
{
public:
	IProgram() : m_isActive(false), m_vert(nullptr), m_frag(nullptr) {};
	IProgram(InternalResource<ShaderDerived>* vert, InternalResource<ShaderDerived>* frag) : m_isActive(false), m_vert(vert), m_frag(frag) {};

	virtual bool init() = 0;
	virtual void destroy() = 0;
	virtual void use() = 0;
	virtual void unuse() = 0;

protected:
	// NOTE: to be used for checking bound usage only, not dereferencing.
	inline static IProgram* programInUse = nullptr;

	bool m_isActive;

	InternalResource<ShaderDerived>* m_vert;
	InternalResource<ShaderDerived>* m_frag;
};

} // Engine

#endif // !IPROGRAM_H
