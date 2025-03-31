#include "SourceCodeResource.h"

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
    : Resource(Type::SourceCode, "NoName"), m_path("NoPath")
{
}

SourceCodeResource::SourceCodeResource(const std::string& name, const std::string& path)
    : Resource(Type::SourceCode, name), m_path(path)
{
}

void SourceCodeResource::load()
{
    bool openedFile;
    m_data = fileToString(m_path, openedFile);

    m_loaded = openedFile;
}

void SourceCodeResource::unload()
{
    m_loaded = false;

    m_data = "";
}


} // Engine