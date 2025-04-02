#include "SpriteComponent.h"

namespace Engine {
namespace GameObjects {

InternalResource<Program> * SpriteComponent::cachedProgResource = nullptr;

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
	if (!cachedProgResource)
	{
		auto& vertexResource = ResourceManager<SourceCodeResource>::getInstance().store(SourceCodeResource("defaultVert", "./assets/shaders/default.vert"));
		auto& fragmentResource = ResourceManager<SourceCodeResource>::getInstance().store(SourceCodeResource("defaultFrag", "./assets/shaders/default.frag"));

		Shader vertShader(&vertexResource, Shader::Type::Vertex);
		auto& vertShaderResource = ResourceManager<InternalResource<Shader>>::getInstance().store(InternalResource("vertShader", vertShader));

		Shader fragShader(&fragmentResource, Shader::Type::Fragment);
		auto& fragShaderResource = ResourceManager<InternalResource<Shader>>::getInstance().store(InternalResource("fragShader", fragShader));

		Program prog(&vertShaderResource, &fragShaderResource);
		auto& progResource = ResourceManager<InternalResource<Program>>::getInstance().store(InternalResource("quadProgram", prog));
		progResource.load();

		cachedProgResource = &progResource; // Cache resource to be used in later calls.
	}
};

void SpriteComponent::update()
{
	// Create 2d quad.
	std::vector<VertexData<float>::Vertex> verticesRaw = {
	{{-0.2f + m_x, -0.2f + m_y}, {m_r, m_g, m_b}}, // Bottom-left  
	{{-0.2f + m_x,  0.2f + m_y}, {m_r, m_g, m_b}}, // Top-left  
	{{ 0.2f + m_x,  0.2f + m_y}, {m_r, m_g, m_b}}, // Top-right  
	{{ 0.2f + m_x, -0.2f + m_y}, {m_r, m_g, m_b}}  // Bottom-right  
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