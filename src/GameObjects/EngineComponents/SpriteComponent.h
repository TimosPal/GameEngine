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
	SpriteComponent(float r, float g, float b) : IComponent<SpriteComponent>() 
	{
		m_r = r;
		m_g = g;
		m_b = b;
	};

	virtual void start() override {};

	virtual void update() override
	{
		// Create 2d quad.
		std::vector<VertexData<float>::Vertex> verticesRaw = {
		{{ -0.5f, -0.5f}, {0.7f, 0.3f, 0.8f}},
		{{  0.5f, -0.5f}, {0.7f, 0.3f, 0.8f}},
		{{  0.0f,  0.5f}, {0.7f, 0.3f, 0.8f}}
		};
		VertexData<float> vertexData(verticesRaw);

		// Submit to renderer.
		RenderData data(m_r, m_g, m_b, 0, 0, 0, vertexData);
		Application::getInstance()->getRenderer().submit(data);
	};

private:
	// TODO: Move to a struct. 
	float m_r, m_g, m_b;
};

} // GameObjects
} // Engine

#endif // !SPRITE_COMPONENT_H