#include "SourceResource.h"

namespace Engine {

SourceResource::SourceResource()
	: SourceResource("")
{}

SourceResource::SourceResource(const std::string& path)
	: m_path(path), m_data("")
{}

bool SourceResource::init()
{
    LOG_INFO("Loading source file : {}", m_path);

    bool loaded = false;
    m_data = fileToString(m_path, loaded);
	if (!loaded)
	{
		LOG_ERROR("Failed to read source file: {}", m_path);
		return false;
	}

    return loaded;
}

void SourceResource::destroy()
{
    LOG_INFO("Unloading source file : {}", m_path);

    m_data = "";
}

} // Engine