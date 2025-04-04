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
    GenericHandler() : IResourceHandler(IResourceHandler::Type::Internal, "NoName") {}
    GenericHandler(const std::string& name, const IResourceDerived& internal) : IResourceHandler(IResourceHandler::Type::Internal, name), m_internal(internal) {}

    ~GenericHandler()
    {
        unload();
    }

    bool load() override 
    {
        // FIXME: if internal is init already, m_loaded should be init properly not to false!
        if (!m_loaded)
        {
			LOG_INFO("Loading resource: {}", m_name);
            m_loaded = m_internal.init();
            if (!m_loaded)
            {
                LOG_ERROR("Resource not loaded: {}", m_name);
            }
        }

        return m_loaded;
    }

    void unload() override
    {
        if (m_loaded)
        {
            LOG_INFO("Unloading resource: {}", m_name);
            m_loaded = false;
            m_internal.destroy();
        }
    }

    IResourceDerived& getResource() { return m_internal; }

private:
    IResourceDerived m_internal;
};

} // Engine

#endif // !INTERNAL_RESOURCE_H
