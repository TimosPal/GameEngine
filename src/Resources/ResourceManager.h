#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <unordered_map>

#include "Resource.h"

namespace Engine {

template<typename ResourceType>
class ResourceManager
{
public:
	static ResourceManager& getInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	ResourceType& store(ResourceType&& newResource)
	{
		// Try to find handle.
		auto resource = m_handles.find(newResource.getName());
		if (resource != m_handles.end())
		{
			// Already loaded.
			return m_resources[resource->second];
		}
		else
		{
			// Needs loading.
			Identifier id = newResource.getID();
			m_handles[newResource.getName()] = id;
			m_resources[id] = std::move(newResource);

			return m_resources[id];
		}
	}

	ResourceType& load(const std::string& name)
	{
		// Try to find handle.
		auto resource = m_handles.find(name);
		if (resource != m_handles.end())
		{
			// Already loaded.
			return m_resources[resource->second];
		}
		else
		{
			SPDLOG_CRITICAL("Resource {} not found", name);
			return getInvalidResource();
		}
	}

	ResourceType& load(Identifier id)
	{
		// Try to find resource.
		auto resource = m_resources.find(id);
		if (resource != m_resources.end())
		{
			return resource->second;
		}
		else
		{
			SPDLOG_CRITICAL("Resource {} not found", id);
			return getInvalidResource();
		}
	}

private:
	std::unordered_map<Identifier, ResourceType> m_resources;
	std::unordered_map<std::string, Identifier> m_handles;

	ResourceManager() {};

	ResourceType& getInvalidResource()
	{
		static ResourceType invalid;
		return invalid;
	}
};

} // Engine

#endif // !RESOURCE_MANAGER_H
