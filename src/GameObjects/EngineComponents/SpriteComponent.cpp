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
	{{ m_x + -0.02f, m_y + -0.02f}, {m_r, m_g, m_b}},
	{{ m_x + 0.02f, m_y + -0.02f}, {m_r, m_g, m_b}},
	{{ m_x + 0.0f, m_y + 0.02f}, {m_r, m_g, m_b}}
	};
	VertexData<float> vertexData(verticesRaw);

	// Submit to renderer.
	RenderData data(vertexData, cachedProgResource->getInternalObject());
	Application::getInstance()->getRenderer().submit(data);
};

} // GameObjects
} // Engine