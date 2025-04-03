#include "SpriteComponent.h"

#include <Utility/Logger.h>
#include <Core/Application.h>

#include <Resources/ResourceManager.h>
#include <Resources/SourceHandler.h>
#include <Resources/TextureHandler.h>

#include <Graphics/GraphicsIncludes.h>

namespace Engine {
namespace GameObjects {

InternalHandler<ProgramImpl> * SpriteComponent::cachedProgHandler = nullptr;

SpriteComponent::SpriteComponent(float r, float g, float b, float x, float y)
	: IComponent<SpriteComponent>()
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_x = x;
	m_y = y;
};

void SpriteComponent::start() 
{
	TextureResource texture("TestTexture", "./assets/textures/wall.jpg");
	texture.load();

	if (!cachedProgHandler)
	{
		auto& vertexHandler = ResourceManager<SourceHandler>::getInstance().store(SourceHandler("defaultVert", "./assets/shaders/default.vert"));
		auto& fragmentHandler = ResourceManager<SourceHandler>::getInstance().store(SourceHandler("defaultFrag", "./assets/shaders/default.frag"));

		ShaderImpl vertShader(&vertexHandler, ShaderImpl::Type::Vertex);
		auto& vertShaderResource = ResourceManager<InternalHandler<Shader>>::getInstance().store(InternalHandler("vertShader", vertShader));

		ShaderImpl fragShader(&fragmentHandler, ShaderImpl::Type::Fragment);
		auto& fragShaderResource = ResourceManager<InternalHandler<Shader>>::getInstance().store(InternalHandler("fragShader", fragShader));

		ProgramImpl prog(&vertShaderResource, &fragShaderResource);
		auto& progHandler = ResourceManager<InternalHandler<ProgramImpl>>::getInstance().store(InternalHandler("quadProgram", prog));
		progHandler.load();

		cachedProgHandler = &progHandler; // Cache resource to be used in later calls.
	}
};

void SpriteComponent::update()
{
	// Create 2d quad.
	// [x,y][r,g,b][u,v]
	std::vector<VertexData<float>::Vertex> verticesRaw = {
	{{-0.05f + m_x, -0.05f + m_y}, {m_r, m_g, m_b}, {0.0f, 0.0f}}, // Bottom-left  
	{{-0.05f + m_x,  0.05f + m_y}, {m_r, m_g, m_b}, {0.0f, 1.0f}}, // Top-left  
	{{ 0.05f + m_x,  0.05f + m_y}, {m_r, m_g, m_b}, {1.0f, 1.0f}}, // Top-right  
	{{ 0.05f + m_x, -0.05f + m_y}, {m_r, m_g, m_b}, {1.0f, 0.0f}}  // Bottom-right  
	};

	// Indexing data. (Reduces 6 vertices to 4)
	std::vector<unsigned int> indicesRaw = {
		0, 2, 1,  // First triangle (Clockwise)  
		0, 3, 2   // Second triangle (Clockwise)  
	};

	// Submit to renderer.
	RenderData data(verticesRaw, indicesRaw, cachedProgHandler->getResource());
	Application::getInstance()->getRenderer().submit(std::move(data));
};

} // GameObjects
} // Engine