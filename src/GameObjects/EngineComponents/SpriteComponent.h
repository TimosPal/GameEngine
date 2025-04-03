#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <GameObjects/IComponent.h>
#include <Resources/InternalResource.h>

#include <Graphics/GraphicsIncludes.h>

namespace Engine {
namespace GameObjects {

class SpriteComponent : public IComponent<SpriteComponent>
{
public:
	SpriteComponent(float r, float g, float b, float x, float y);

	virtual void start() override;
	virtual void update() override;

	// TODO: Move to a struct. 
	// Not public.
	float m_r, m_g, m_b;
	float m_x, m_y;
private:
	static InternalResource<ProgramImpl>* cachedProgResource;
};

} // GameObjects
} // Engine

#endif // !SPRITE_COMPONENT_H