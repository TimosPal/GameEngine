#include "ShaderResource.h"

namespace Engine {

ShaderResource::ShaderResource() : Resource::Resource() {}

ShaderResource::ShaderResource(const std::string& name, const std::string& path)
    : Resource(name, path, Resource::Type::Shader, IdentifierGenerator<Resource>::getInstanceID<ShaderResource>())
{
}

ShaderResource::ShaderResource(const ShaderResource& other)
    : Resource(other)
{
}

ShaderResource& ShaderResource::operator=(const ShaderResource& other)
{
    if (this != &other)
    {
        Resource::operator=(other);
    }
    return *this;
}

ShaderResource::ShaderResource(ShaderResource&& other) noexcept
    : Resource(std::move(other))
{
}

ShaderResource& ShaderResource::operator=(ShaderResource&& other) noexcept
{
    if (this != &other)
    {
        Resource::operator=(std::move(other));
    }
    return *this;
}

const std::string& ShaderResource::getString()
{
    if (!m_loaded)
    {
        load();
    }

    return m_data;
}

void ShaderResource::load()
{
    bool openedFile;
    m_data = fileToString(m_path, openedFile);

    m_loaded = openedFile;
}

void ShaderResource::unload()
{
    m_loaded = false;

    m_data = "";
}


} // Engine