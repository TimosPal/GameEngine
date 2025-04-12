#ifndef INTERNAL_RESOURCE_H
#define INTERNAL_RESOURCE_H

#include <Resources/Handlers/IResourceHandler.h>
#include <Utility/Logger.h>

namespace Engine {

// Provides a generic resouce handle for any type that support the IResource interface.
// For any other case IResourceHandler can be extended for other custom implementations.
template <typename IResourceDerived>
struct GenericHandler : public IResourceHandler
{
public:
    GenericHandler() : IResourceHandler("NoName") {}
    GenericHandler(const std::string& name, const IResourceDerived& internal) : IResourceHandler(name), m_internal(internal) {}

    ~GenericHandler()
    {
        unload();
    }

    bool load() override 
    {
        // FIXME: if internal is init already, m_loaded should be init properly not to false!
        if (m_loadedCount == 0)
        {
			LOG_INFO("Loading resource: {}", m_name);
            bool loaded = m_internal.init();
            if (!loaded)
            {
                LOG_ERROR("Resource not loaded: {}", m_name);
                return false;
            }
        }

        return ++m_loadedCount > 0;
    }

    void unload() override
    {
        if (m_loadedCount > 0 && --m_loadedCount == 0)
        {
            LOG_INFO("Unloading resource: {}", m_name);
            m_internal.destroy();
        }
    }

    IResourceDerived& getResource() { return m_internal; }

private:
    IResourceDerived m_internal;
};

} // Engine

#endif // !INTERNAL_RESOURCE_H
