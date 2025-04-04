#ifndef ISHADER_H
#define ISHADER_H

#include <Resources/SystemResources/SourceResource.h>
#include <Resources/Handlers/GenericHandler.h>
#include <Resources/SystemResources/IResource.h>

namespace Engine {

class IShader : public IResource
{
public:
	enum class Type {
		Vertex, Fragment, None
	};

	IShader() : m_shader(nullptr), m_type(Type::None), m_isActive(false) {}
	IShader(GenericHandler<SourceResource>* shader, Type type) : m_shader(shader), m_type(type), m_isActive(false) {}

protected:
	GenericHandler<SourceResource>* m_shader;

	Type m_type;
	bool m_isActive;
};

} // Engine

#endif // !ISHADER_H
