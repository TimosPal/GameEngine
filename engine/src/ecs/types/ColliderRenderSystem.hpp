#ifndef COLLIDER_RENDER_SYSTEM_HPP
#define COLLIDER_RENDER_SYSTEM_HPP

#include "ecs/ISystem.hpp"
#include "ecs/types/EngineComponents.hpp"
#include "renderer/Renderer2D.hpp"
#include "utilities/misc.hpp"

#include "physics/aabb.hpp"

namespace Engine {

class ColliderRenderSystem : public ISystem {
public:
	ColliderRenderSystem(std::shared_ptr<Renderer2D> renderer2D) : m_renderer2D(renderer2D) {}

	virtual void update(float deltaTime) override
	{
		auto& activeWorld = getSceneManager().getActiveScene()->getWorld();
		activeWorld.query<AABB, TransformComponent>().each([this](ID entityID, AABB* aabb, TransformComponent* transformComp) {
			// Draw AABB as a rectangle
			glm::vec2 min = aabb->Min * transformComp->Size + transformComp->Position;
			glm::vec2 max = aabb->Max * transformComp->Size + transformComp->Position;
			glm::vec4 color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); // Green color for AABB

			m_renderer2D->drawSquare(min, max, color);
		});
	}

private:
	std::shared_ptr<Renderer2D> m_renderer2D;
};

} // Engine

#endif // !COLLIDER_RENDER_SYSTEM_HPP
