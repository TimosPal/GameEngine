#ifndef TEXTURE_H
#define TEXTURE_H

#include <Resources/TextureHandler.h>

namespace Engine {

class Texture
{
public:
	Texture();
	Texture(TextureResource* texture);
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