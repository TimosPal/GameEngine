#include "Texture.h"

#include <glad/glad.h>

namespace Engine {

Texture::Texture()
{
	glGenTextures(1, &m_glTexture);
}

Texture::Texture(GenericHandler<TextureResource>* texture)
{
}

Texture::~Texture()
{
}

bool Texture::init()
{
	return false;
}

void Texture::destroy()
{
}

void Texture::bind()
{
}

void Texture::unbind()
{
}

} // Engine