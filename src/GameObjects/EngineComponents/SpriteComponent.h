#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <GameObjects/IComponent.h>
#include <Core/Application.h>

#include <Utility/Logger.h>

namespace Engine {
namespace GameObjects {

class SpriteComponent : public IComponent<SpriteComponent>
{
public:
	SpriteComponent(float r, float g, float b, float x, float y) : IComponent<SpriteComponent>() 
	{
		m_r = r;
		m_g = g;
		m_b = b;
		m_x = x;
		m_y = y;
	};

	virtual void start() override {};

	virtual void update() override
	{
		// Create 2d quad.
		std::vector<VertexData<float>::Vertex> verticesRaw = {
		{{ m_x + -0.02f, m_y + -0.02f}, {m_r, m_g, m_b}},
		{{ m_x +  0.02f, m_y + -0.02f}, {m_r, m_g, m_b}},
		{{ m_x +  0.0f, m_y +  0.02f}, {m_r, m_g, m_b}}
		};
		VertexData<float> vertexData(verticesRaw);

		// Submit to renderer.
		RenderData data(vertexData);
		Application::getInstance()->getRenderer().submit(data);
	};

	// TODO: Move to a struct. 
	// Not public.
	float m_r, m_g, m_b;
	float m_x, m_y;
private:
};

} // GameObjects
} // Engine

#endif // !SPRITE_COMPONENT_H