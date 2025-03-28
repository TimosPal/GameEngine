#include "VBO.h"

#include <glad/glad.h>

namespace Engine {

VBO* VBO::boundVBO = nullptr;

// Utility function to get the correct OpenGL type
template<typename T>
constexpr GLenum getGLType()
{
	if constexpr (std::is_same_v<T, float>) return GL_FLOAT;
	else if constexpr (std::is_same_v<T, int>) return GL_INT;
	else if constexpr (std::is_same_v<T, double>) return GL_DOUBLE;
	else STATIC_ASSERT_FALSE("Invalid VBO type");
}

VBO::VBO(const VertexData<float>& data, int drawingType)
	: m_drawingType(drawingType), m_data(data), m_glVBO(-1)
{
	init();
}

VBO::~VBO()
{
	m_isActive = false;
	boundVBO = nullptr;
	glDeleteBuffers(1, &m_glVBO);
}

void VBO::setAttributes()
{
	bind();

	// Initialize each attribute.
	for (const auto& attributeInfo : m_data.getInfo())
	{
		glVertexAttribPointer(
			attributeInfo.attributeLocation, // Attribute location
			attributeInfo.elementsCount, // Attribute elements count
			getGLType<float>(), // Attribute type
			GL_FALSE,
			m_data.getVertexSize(), // #Bytes per vertex
			(void*)(attributeInfo.startingOffset * sizeof(float)) // Attribute starting offset
		);
		glEnableVertexAttribArray(attributeInfo.attributeLocation);
	}

	unbind();
}

void VBO::updateData(const VertexData<float>& data)
{
	m_data = data;

	bind();
	glBufferData(GL_ARRAY_BUFFER, m_data.getFlatVec().size() * sizeof(float), m_data.getFlatVec().data(), m_drawingType);
	unbind();
}

void VBO::bind()
{
	if (boundVBO == this)
		return;

	boundVBO = this;
	glBindBuffer(GL_ARRAY_BUFFER, m_glVBO);
}

void VBO::unbind()
{
	if (boundVBO != this)
		return;

	boundVBO = nullptr;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::init()
{
	m_isActive = true;
	glGenBuffers(1, &m_glVBO);

	bind();
	glBufferData(GL_ARRAY_BUFFER, m_data.getFlatVec().size() * sizeof(float), m_data.getFlatVec().data(), m_drawingType);
	unbind();
}

}