#include "ShaderResource.h"

namespace Engine {

ShaderResource::ShaderResource() : Resource::Resource() {}

ShaderResource::ShaderResource(const std::string& name, const std::string& path)
    : Resource(name, path, Resource::Type::Shader, IdentifierGenerator<Resource>::getTypeID<ShaderResource>())
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

std::string ShaderResource::getString()
{
    if (!m_loaded)
    {
        bool openedFile;
        m_data = fileToString(path, openedFile);

        m_loaded = openedFile;
    }

    return m_data;
}

void ShaderResource::unload()
{
    m_loaded = false;
}


} // Engine