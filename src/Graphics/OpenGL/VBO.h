#ifndef VBO_H
#define VBO_H

#include <Graphics/Mesh.h>
#include <Utility/Assertions.h>

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
class VBO
{
public:
	VBO(Mesh::AttributeInfo info, int drawingType);
	VBO(std::vector<float>* data, Mesh::AttributeInfo info, int drawingType);
	~VBO();

	void setAttributes();
	void updateData(std::vector<float>* data);
	void bind();
	void unbind();

	int getVertCount() const { return 0; }
	unsigned int getGLVBO() const { return m_glVBO; }

private:
	static VBO* boundVBO;
	bool m_isActive = false;

	unsigned int m_glVBO;
	int m_drawingType;

	std::vector<float>* m_data;
	Mesh::AttributeInfo m_info;

	void init();
};

} // Engine

#endif // !VBO_H