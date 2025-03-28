#ifndef VBO_H
#define VBO_H

#include <Graphics/VertexData.h>
#include <Utility/Assertions.h>

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
class VBO
{
public:
	VBO(const VertexData<float>& data, int drawingType);

	~VBO();

	void setAttributes();
	void updateData(const VertexData<float>& data);
	void bind();
	void unbind();

	int getVertCount() const { return int(m_data.getFlatVec().size()); }
	unsigned int getGLVBO() const { return m_glVBO; }

private:
	static VBO* boundVBO;

	unsigned int m_glVBO;
	int m_drawingType;
	bool m_isActive = false;

	VertexData<float> m_data;

	void init();
};

} // Engine

#endif // !VBO_H