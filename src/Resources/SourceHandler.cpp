#include "SourceHandler.h"

#include <Utility/IdentifierGenerator.h>

namespace Engine {

const std::string& SourceHandler::getData()
{
    if (!m_loaded)
    {
        load();
    }

    return m_data;
}

SourceHandler::SourceHandler()
    : IResourceHandler(Type::SourceCode, "NoName"), m_path("NoPath")
{
}

SourceHandler::~SourceHandler(){
    unload();
}

SourceHandler::SourceHandler(const std::string& name, const std::string& path)
    : IResourceHandler(Type::SourceCode, name), m_path(path)
{
}

void SourceHandler::load()
{
    if (!m_loaded)
    {
        LOG_INFO("Loading source code resource: {}", m_path);
        m_data = fileToString(m_path, m_loaded);
        m_loaded = true;
    }
}

void SourceHandler::unload()
{
    if (m_loaded)
    {
        LOG_INFO("Unloading source code resource: {}", m_path);
        m_loaded = false;
        m_data = "";
    }
}


} // Engine