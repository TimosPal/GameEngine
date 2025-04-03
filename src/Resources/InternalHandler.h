#ifndef INTERNAL_RESOURCE_H
#define INTERNAL_RESOURCE_H

#include <Resources/IResourceHandler.h>

namespace Engine {

template <typename InternalDerived>
struct InternalResource : public IResourceHandler
{
public:
    InternalResource() : IResourceHandler(IResourceHandler::Type::Internal, "NoName") {}
    InternalResource(const std::string& name, const InternalDerived& internal) : IResourceHandler(IResourceHandler::Type::Internal, name), m_internal(internal) {}

    ~InternalResource()
    {
        unload();
    }

    void load() override 
    {
        // FIXME: if internal is init already, m_loaded should be init properly not to false!
        if (!m_loaded)
        {
			LOG_INFO("Loading internal resource: {}", m_name);
            m_internal.init(); 
            m_loaded = true;
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

    InternalDerived& getInternalObject() { return m_internal; }

private:
    InternalDerived m_internal;
};

} // Engine

#endif // !INTERNAL_RESOURCE_H
