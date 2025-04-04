#ifndef TEXTURE_H
#define TEXTURE_H

#include <Resources/Handlers/GenericHandler.h>
#include <Resources/SystemResources/TextureResource.h>

namespace Engine {

class Texture
{
public:
	Texture();
	Texture(GenericHandler<TextureResource>* texture);
	~Texture();

	bool init();
	void destroy();

	void bind();
	void unbind();

	unsigned int getGLTexture() const { return m_glTexture; }
private:
	unsigned int m_glTexture;
};

} // Engine

#endif // !TEXTURE_H