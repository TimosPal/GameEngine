#ifndef ITEXTURE_H
#define ITEXTURE_H

#include <Resources/SystemResources/TextureResource.h>
#include <Resources/Handlers/GenericHandler.h>
#include <Resources/SystemResources/IResource.h>

namespace Engine {

class ITexture : public IResource
{
public:
	ITexture() : m_texture(nullptr), m_isActive(false) {}
	ITexture(GenericHandler<TextureResource>* texture) : m_texture(texture), m_isActive(false) {}

protected:
	// NOTE: to be used for checking bound usage only, not dereferencing.
	inline static ITexture* textureInUse = nullptr;

	GenericHandler<TextureResource>* m_texture;

	bool m_isActive;
};

} // Engine

#endif // !ITEXTURE_H
