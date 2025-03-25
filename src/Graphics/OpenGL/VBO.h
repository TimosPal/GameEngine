#ifndef VBO_H
#define VBO_H

#include <Utility/Assertions.h>
#include <glad/glad.h>

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
template<typename T>
class VBO
{
public:
	VBO(const std::vector<T>& data, int attributeIndex, int elementsPerStride, int drawingType = GL_STATIC_DRAW)
		: m_elementsPerStride(elementsPerStride), m_drawingType(drawingType), m_attributeIndex(attributeIndex),
		m_data(data), m_glVBO(-1)
	{}

	~VBO() 
	{
		glDeleteBuffers(1, &m_glVBO);
	}

	void init()
	{
		glGenBuffers(1, &m_glVBO);
		
		bind();
		glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(T), m_data.data(), m_drawingType);
		glVertexAttribPointer(m_attributeIndex, m_elementsPerStride, getGLType(), GL_FALSE, sizeof(T) * m_elementsPerStride, nullptr);
		glEnableVertexAttribArray(m_attributeIndex);
	}

	void bind()
	{
		// TODO: save previous bind state?
		glBindBuffer(GL_ARRAY_BUFFER, m_glVBO);
	}

	int getVertCount() const { return m_data.size() / m_elementsPerStride; }

	unsigned int getGLVBO() const { return m_glVBO; }

private:
	unsigned int m_glVBO;

	int m_elementsPerStride;
	int m_drawingType;
	int m_attributeIndex;

	std::vector<T> m_data;

	// Utility function to get the correct OpenGL type
	constexpr GLenum getGLType()
	{
		if constexpr (std::is_same_v<T, float>) return GL_FLOAT;
		else if constexpr (std::is_same_v<T, int>) return GL_INT;
		else if constexpr (std::is_same_v<T, double>) return GL_DOUBLE;
		else STATIC_ASSERT_FALSE("Invalid VBO type");
	}
};

} // Engine

#endif // !VBO_H