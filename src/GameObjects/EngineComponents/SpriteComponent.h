#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "IComponent.h"
#include "Core/Application.h"
#include "Graphics/IRenderer.h"

namespace Engine {

class SpriteComponent : public IComponent<SpriteComponent>
{
public:
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
		RenderData& data(x, y, z, r, g, b, vertexData);
		Application::getInstance()->getRenderer()->submit(data);
	};

	// todo: private
	float r = 0, g = 0, b = 0;
	float x = 0, y = 0, z = 0;
private:
};

} // Engine

#endif // !SPRITE_COMPONENT_H
