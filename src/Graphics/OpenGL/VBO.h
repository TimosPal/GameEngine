#ifndef VBO_H
#define VBO_H

#include "VertexData.h"
#include <Utility/Assertions.h>
#include <glad/glad.h>

namespace Engine {

// NOTE: This class could be abstracted in the future, if more APIs are to be used.
template<typename T>
class VBO
{
public:
	VBO(const VertexData<T>& data, int drawingType = GL_STATIC_DRAW)
		: m_drawingType(drawingType), m_data(data), m_glVBO(-1)
	{}

	~VBO() 
	{
		m_isActive = false;
		boundVBO = nullptr;
		glDeleteBuffers(1, &m_glVBO);
	}

	void init()
	{
		m_isActive = true;
		glGenBuffers(1, &m_glVBO);
		
		bind();
		glBufferData(GL_ARRAY_BUFFER, m_data.getFlatVec().size() * sizeof(T), m_data.getFlatVec().data(), m_drawingType);
		unbind();
	}

	void setAttributes()
	{
		bind();

		// Initialize each attribute.
		for (const auto& attributeInfo : m_data.getInfo())
		{
			glVertexAttribPointer(
				attributeInfo.attributeLocation, // Attribute location
				attributeInfo.elementsCount, // Attribute elements count
				getGLType(), // Attribute type
				GL_FALSE,
				m_data.getVertexSize(), // #Bytes per vertex
				(void*)(attributeInfo.startingOffset * sizeof(T)) // Attribute starting offset
			);
			glEnableVertexAttribArray(attributeInfo.attributeLocation);
		}

		unbind();
	}

	void updateData(const VertexData<T>& data)
	{
		m_data = data;

		bind();
		glBufferData(GL_ARRAY_BUFFER, m_data.getFlatVec().size() * sizeof(T), m_data.getFlatVec().data(), m_drawingType);
		unbind();
	}

	void bind()
	{
		if (boundVBO == this)
			return;

		boundVBO = this;
		glBindBuffer(GL_ARRAY_BUFFER, m_glVBO);
	}

	void unbind()
	{
		if (boundVBO != this)
			return;

		boundVBO = nullptr;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	int getVertCount() const { return m_data.getFlatVec().size(); }

	unsigned int getGLVBO() const { return m_glVBO; }

private:
	inline static VBO* boundVBO = nullptr;

	unsigned int m_glVBO;
	int m_drawingType;

	VertexData<T> m_data;

	bool m_isActive = false;

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