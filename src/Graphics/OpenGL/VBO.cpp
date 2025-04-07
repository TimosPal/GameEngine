#include "VBO.h"

#include "GLWrapper.h"

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

VBO::VBO(Mesh::AttributeInfo info, int drawingType)
	: m_info(info), m_drawingType(drawingType), m_data(nullptr), m_glVBO(-1)
{
	init();
}

VBO::VBO(std::vector<float>* data, Mesh::AttributeInfo info, int drawingType)
	: m_info(info), m_drawingType(drawingType), m_data(data), m_glVBO(-1)
{
	init();
}

VBO::~VBO()
{
	m_isActive = false;
	if (boundVBO == this)
		boundVBO = nullptr;
	GL(glDeleteBuffers(1, &m_glVBO));
}

void VBO::setAttributes()
{
	bind();

	// Initialize each attribute.
	int offset = 0;
	for (int i = 0; i < m_info.shaderLocations.size(); i++)
	{
		GL(glVertexAttribPointer(
			m_info.shaderLocations[i], // Attribute location
			m_info.elementsCount[i], // Attribute elements count
			getGLType<float>(), // Attribute type
			GL_FALSE,
			m_info.totalElementsPerVertex * sizeof(float), // #Bytes per vertex
			(void*)(offset * sizeof(float)) // Attribute starting offset
		));
		GL(glEnableVertexAttribArray(m_info.shaderLocations[i]));

		offset += m_info.elementsCount[i];
	}

	unbind();
}

void VBO::updateData(std::vector<float>* data)
{
	m_data = data;

	bind();
	GL(glBufferData(GL_ARRAY_BUFFER, m_data->size() * sizeof(float), m_data->data(), m_drawingType));
	unbind();
}

void VBO::bind()
{
	if (boundVBO == this)
		return;

	boundVBO = this;
	GL(glBindBuffer(GL_ARRAY_BUFFER, m_glVBO));
}

void VBO::unbind()
{
	if (boundVBO != this)
		return;

	boundVBO = nullptr;
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VBO::init()
{
	m_isActive = true;
	GL(glGenBuffers(1, &m_glVBO));

	if (m_data)
	{
		bind();
		GL(glBufferData(GL_ARRAY_BUFFER, m_data->size() * sizeof(float), m_data->data(), m_drawingType));
		unbind();
	}
}

}