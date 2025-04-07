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
	: IComponent<SpriteComponent>(), m_texturePath(texturePath), m_quad(x, y, 0.02f, 0.02f, r, g, b)
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
	m_quad.updateX(m_x);
	m_quad.updateY(m_y);
	m_quad.updateR(m_r);
	m_quad.updateG(m_g);
	m_quad.updateB(m_b);

	// Submit to renderer.
	RenderData data(
		m_quad,
		cachedProgHandler->getResource(),
		cachedTextureHandler->getResource()
	);
	Application::getInstance()->getRenderer().submit(std::move(data));
};

} // GameObjects
} // Engine