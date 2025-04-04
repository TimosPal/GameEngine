#ifndef IRESOURCE_HANDLER_H  
#define IRESOURCE_HANDLER_H  

#include <Utility/IdentifierGenerator.h>  
#include <string>

namespace Engine {  

struct IResourceHandler
{  
public:
    enum class Type {  
        Internal, Image, SourceCode, Sound, None  
    };

    // Could split IDs per resource type if needed.
    IResourceHandler(const Type type, const std::string& name) 
        : m_name(name), m_loaded(false), m_type(type), m_id(IdentifierGenerator<IResourceHandler>::getInstanceID<IResourceHandler>()) {}
	IResourceHandler() 
        : IResourceHandler(Type::None, "NoName") {}

    const std::string& getName() { return m_name; }
    const Type getType() { return m_type; }
    const Identifier getID() { return m_id; }

    virtual bool load() = 0;
    virtual void unload() = 0;

protected:

    bool m_loaded;
    Type m_type;
    
    std::string m_name;
    Identifier m_id;
};  

} // Engine  

#endif // !IRESOURCE_HANDLER_H
