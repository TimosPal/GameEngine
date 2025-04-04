#include "EBO.h"


#include <Utility/Logger.h>
#include "GLWrapper.h"

namespace Engine {

EBO* EBO::boundEBO = nullptr;

EBO::EBO(int drawingType)
    : m_drawingType(drawingType)
{
    glGenBuffers(1, &m_glEBO);
}

EBO::EBO(const std::vector<unsigned int>& indices, int drawingType)
    : m_indices(indices), m_drawingType(drawingType)
{
    GL(glGenBuffers(1, &m_glEBO));

    bind();
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), m_drawingType));
    unbind();
}

EBO::~EBO()
{
    if (boundEBO == this)
        boundEBO = nullptr;
    GL(glDeleteBuffers(1, &m_glEBO));
}

void EBO::bind()
{
    if (boundEBO == this) 
    {
        return;
    }

    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glEBO));
    boundEBO = this;
}

void EBO::unbind()
{
    if (boundEBO != this)
    {
        return;
    }

    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    boundEBO = nullptr;
}

void EBO::updateData(const std::vector<unsigned int>& data)
{
    m_indices = data;

    bind();
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), m_drawingType));
    unbind();
}

} // Engine