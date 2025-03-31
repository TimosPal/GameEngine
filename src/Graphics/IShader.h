#ifndef ISHADER_H
#define ISHADER_H

#include <Resources/SourceCodeResource.h>

namespace Engine {

class IShader
{
public:
	enum class Type {
		Vertex, Fragment, None
	};

	IShader() : m_shader(nullptr), m_type(Type::None), m_isActive(false) {}
	IShader(SourceCodeResource* shader, Type type) : m_shader(shader), m_type(type), m_isActive(false) {}

	virtual bool init() = 0;
	virtual void destroy() = 0;

protected:
	SourceCodeResource* m_shader;

	Type m_type;
	bool m_isActive;
};

} // Engine

#endif // !ISHADER_H
