#include "SpriteComponent.h"

#include <Utility/Logger.h>
#include <Core/Application.h>

#include <Resources/ResourceManager.h>
#include <Resources/SystemResources/TextureResource.h>
#include <Resources/SystemResources/SourceResource.h>

#include <Graphics/GraphicsIncludes.h>

namespace Engine {
namespace GameObjects {

SpriteComponent::SpriteComponent(std::string texturePath, float r, float g, float b, float x, float y)
	: IComponent<SpriteComponent>(), m_texturePath(texturePath)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_x = x;
	m_y = y;
};

void SpriteComponent::start() 
{
	if (!cachedProgHandler)
	{
		SourceResource vertSource("./assets/shaders/default.vert");
		auto& vertexSourceHandler = ResourceManager<GenericHandler<SourceResource>>::getInstance().store(GenericHandler("defaultVertSource", vertSource));

		SourceResource fragSource("./assets/shaders/default.frag");
		auto& fragmentSourceHandler = ResourceManager<GenericHandler<SourceResource>>::getInstance().store(GenericHandler("defaultFragSource", fragSource));

		ShaderImpl vertShader(&vertexSourceHandler, ShaderImpl::Type::Vertex);
		auto& vertShaderResource = ResourceManager<GenericHandler<Shader>>::getInstance().store(GenericHandler("vertShader", vertShader));

		ShaderImpl fragShader(&fragmentSourceHandler, ShaderImpl::Type::Fragment);
		auto& fragShaderResource = ResourceManager<GenericHandler<Shader>>::getInstance().store(GenericHandler("fragShader", fragShader));

		ProgramImpl prog(&vertShaderResource, &fragShaderResource);
		auto& progHandler = ResourceManager<GenericHandler<ProgramImpl>>::getInstance().store(GenericHandler("quadProgram", prog));
		progHandler.load();

		vertexSourceHandler.unload();
		fragmentSourceHandler.unload();

		cachedProgHandler = &progHandler; // Cache resource to be used in later calls.
	}

	if (!cachedTextureHandler)
	{
		TextureResource textureResource(m_texturePath);
		auto& textureResourceHandler = ResourceManager<GenericHandler<TextureResource>>::getInstance().store(GenericHandler("textureResourceTest", textureResource));

		TextureImpl texture(&textureResourceHandler);
		auto& textureHandler = ResourceManager<GenericHandler<TextureImpl>>::getInstance().store(GenericHandler("textureTest", texture));
		textureHandler.load();

		cachedTextureHandler = &textureHandler; // Cache resource to be used in later calls.
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
	RenderData data(
		verticesRaw,
		indicesRaw,
		cachedProgHandler->getResource(),
		cachedTextureHandler->getResource()
	);
	Application::getInstance()->getRenderer().submit(std::move(data));
};

} // GameObjects
} // Engine