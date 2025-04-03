#ifndef INTERNAL_RESOURCE_H
#define INTERNAL_RESOURCE_H

#include <Resources/IResourceHandler.h>

namespace Engine {

template <typename IResourceDerived>
struct InternalHandler : public IResourceHandler
{
public:
    InternalHandler() : IResourceHandler(IResourceHandler::Type::Internal, "NoName") {}
    InternalHandler(const std::string& name, const IResourceDerived& internal) : IResourceHandler(IResourceHandler::Type::Internal, name), m_internal(internal) {}

    ~InternalHandler()
    {
        unload();
    }

    void load() override 
    {
        // FIXME: if internal is init already, m_loaded should be init properly not to false!
        if (!m_loaded)
        {
			LOG_INFO("Loading internal resource: {}", m_name);
            m_loaded = m_internal.init();
            if (!m_loaded)
            {
                LOG_ERROR("Resource not loaded: {}", m_name);
            }
        }
    }

    void unload() override
    {
        if (m_loaded)
        {
            LOG_INFO("Unloading internal resource: {}", m_name);
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
