#ifndef IRESOURCE_HANDLER_H  
#define IRESOURCE_HANDLER_H  

#include <Utility/IdentifierGenerator.h>  
#include <string>

namespace Engine {  

struct IResourceHandler
{  
public:

    // Could split IDs per resource type if needed.
    IResourceHandler(const std::string& name) 
        : m_name(name), m_loaded(false), m_id(IdentifierGenerator<IResourceHandler>::getInstanceID<IResourceHandler>()) {}
	IResourceHandler() 
        : IResourceHandler("NoName") {}

    const std::string& getName() { return m_name; }
    const Identifier getID() { return m_id; }

    virtual bool load() = 0;
    virtual void unload() = 0;

protected:

    bool m_loaded;
    
    std::string m_name;
    Identifier m_id;
};  

} // Engine  

#endif // !IRESOURCE_HANDLER_H
