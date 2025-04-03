#include "SourceHandler.h"

#include <Utility/IdentifierGenerator.h>

namespace Engine {

const std::string& SourceCodeResource::getData()
{
    if (!m_loaded)
    {
        load();
    }

    return m_data;
}

SourceCodeResource::SourceCodeResource()
    : IResourceHandler(Type::SourceCode, "NoName"), m_path("NoPath")
{
}

SourceCodeResource::~SourceCodeResource(){
    unload();
}

SourceCodeResource::SourceCodeResource(const std::string& name, const std::string& path)
    : IResourceHandler(Type::SourceCode, name), m_path(path)
{
}

void SourceCodeResource::load()
{
    if (!m_loaded)
    {
        LOG_INFO("Loading source code resource: {}", m_path);
        m_data = fileToString(m_path, m_loaded);
        m_loaded = true;
    }
}

void SourceCodeResource::unload()
{
    if (m_loaded)
    {
        LOG_INFO("Unloading source code resource: {}", m_path);
        m_loaded = false;
        m_data = "";
    }
}


} // Engine