#ifndef RESOURCE_H  
#define RESOURCE_H  

#include <Utility/IdentifierGenerator.h>  
#include <string>

namespace Engine {  

struct Resource  
{  
public:
    enum class Type {  
        Internal, Image, SourceCode, Sound, None  
    };

    // Could split IDs per resource type if needed.
    Resource(const Type type, const std::string& name) 
        : m_name(name), m_loaded(false), m_type(type), m_id(IdentifierGenerator<Resource>::getInstanceID<Resource>()) {}
	Resource() 
        : Resource(Type::None, "NoName") {}

    const std::string& getName() { return m_name; }
    const Type getType() { return m_type; }
    const Identifier getID() { return m_id; }

    virtual void load() {};
    virtual void unload() {};

protected:

    bool m_loaded;
    Type m_type;
    
    std::string m_name;
    Identifier m_id;
};  

} // Engine  

#endif // !RESOURCE_H
