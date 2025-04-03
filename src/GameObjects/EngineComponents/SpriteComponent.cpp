#include "SpriteComponent.h"

#include <Utility/Logger.h>
#include <Core/Application.h>

#include <Resources/ResourceManager.h>
#include <Resources/SourceCodeResource.h>
#include <Resources/TextureResource.h>

#if GRAPHICS_API == API_OPENGL
	#include <Graphics/OpenGL/Shader.h>
	using ShaderImpl = Engine::Shader;
#else
	#error Invalid graphics API
#endif

namespace Engine {
namespace GameObjects {

InternalResource<ProgramImpl> * SpriteComponent::cachedProgResource = nullptr;

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

	if (!cachedProgResource)
	{
		auto& vertexResource = ResourceManager<SourceCodeResource>::getInstance().store(SourceCodeResource("defaultVert", "./assets/shaders/default.vert"));
		auto& fragmentResource = ResourceManager<SourceCodeResource>::getInstance().store(SourceCodeResource("defaultFrag", "./assets/shaders/default.frag"));

		ShaderImpl vertShader(&vertexResource, ShaderImpl::Type::Vertex);
		auto& vertShaderResource = ResourceManager<InternalResource<Shader>>::getInstance().store(InternalResource("vertShader", vertShader));

		ShaderImpl fragShader(&fragmentResource, ShaderImpl::Type::Fragment);
		auto& fragShaderResource = ResourceManager<InternalResource<Shader>>::getInstance().store(InternalResource("fragShader", fragShader));

		ProgramImpl prog(&vertShaderResource, &fragShaderResource);
		auto& progResource = ResourceManager<InternalResource<ProgramImpl>>::getInstance().store(InternalResource("quadProgram", prog));
		progResource.load();

		cachedProgResource = &progResource; // Cache resource to be used in later calls.
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
	RenderData data(verticesRaw, indicesRaw, cachedProgResource->getInternalObject());
	Application::getInstance()->getRenderer().submit(std::move(data));
};

} // GameObjects
} // Engine