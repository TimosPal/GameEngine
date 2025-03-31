#ifndef INTERNAL_RESOURCE_H
#define INTERNAL_RESOURCE_H

#include <Resources/Resource.h>

namespace Engine {

template <typename InternalDerived>
struct InternalResource : public Resource
{
public:
    InternalResource() : Resource(Resource::Type::Internal, "NoName") {}
    InternalResource(const std::string& name, const InternalDerived& internal) : Resource(Resource::Type::Internal, name), m_internal(internal) {}

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
        LOG_INFO("Unloading internal resource: {}", m_name);
        m_loaded = false;
        m_internal.destroy();
    }

    InternalDerived& getInternalObject() { return m_internal; }

private:
    InternalDerived m_internal;
};

} // Engine

#endif // !INTERNAL_RESOURCE_H
