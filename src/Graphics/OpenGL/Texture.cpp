#include "Texture.h"

#include "GLWrapper.h"

namespace Engine {

Texture::Texture()
	: m_glTexture(0)
{}

Texture::Texture(GenericHandler<TextureResource>* texture)
	: ITexture(texture), m_glTexture(0)
{}

Texture::~Texture()
{}

bool Texture::init()
{
	GL(glGenTextures(1, &m_glTexture));
	bind();

	// TODO: refactor to use constructor arguments for this setup.
	// set the texture wrapping/filtering options (on the currently bound texture object)
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	bool loadedTexture = m_texture->load();
	TextureResource& textureResource = m_texture->getResource();
	GL(glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		textureResource.getWidth(),
		textureResource.getHeight(),
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		textureResource.getData()
	));

	// TODO: Mipmap generation // Handling
	GL(glGenerateMipmap(GL_TEXTURE_2D));

	// TODO: handle more active textures

	unbind();

	m_isActive = true;

	return true;
}

void Texture::destroy()
{
	if (!m_isActive)
		return;

	GL(glDeleteTextures(1, &m_glTexture));
	m_isActive = false;
	m_glTexture = 0;
}

void Texture::bind()
{
	if (!m_isActive || textureInUse == this)
	{
		return;
	}

	glActiveTexture(GL_TEXTURE0);  
	GL(glBindTexture(GL_TEXTURE_2D, m_glTexture));

	textureInUse = this;
}

void Texture::unbind()
{
	if (!m_isActive || textureInUse != this)
	{
		return;
	}

	GL(glBindTexture(GL_TEXTURE_2D, 0));

	textureInUse = nullptr;
}

} // Engine