#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <GameObjects/IComponent.h>
#include <Resources/Handlers/GenericHandler.h>

#include <Graphics/GraphicsIncludes.h>

#include <Graphics/Quad2D.h>

namespace Engine {
namespace GameObjects {

class SpriteComponent : public IComponent<SpriteComponent>
{
public:
	SpriteComponent(std::string texturePath, float r, float g, float b, float x, float y);

	virtual void start() override;
	virtual void update() override;

	// TODO: Move to a struct. 
	// Not public.
	float m_r, m_g, m_b;
	float m_x, m_y;
private:
	inline static GenericHandler<ProgramImpl>* cachedProgHandler = nullptr;
	inline static GenericHandler<TextureImpl>* cachedTextureHandler = nullptr;

	std::string m_texturePath;

	Quad2D m_quad;
};

} // GameObjects
} // Engine

#endif // !SPRITE_COMPONENT_H