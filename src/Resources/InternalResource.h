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
        if (!m_loaded)
        {
            m_internal.init(); 
            m_loaded = true;
        }
    }

    void unload() override 
    {
        m_loaded = false;
        m_internal.destroy();
    }

    InternalDerived& getInternalObject() { return m_internal; }

private:
    InternalDerived m_internal;
};

} // Engine

#endif // !INTERNAL_RESOURCE_H
