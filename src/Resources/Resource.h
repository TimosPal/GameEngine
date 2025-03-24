#ifndef RESOURCE_H  
#define RESOURCE_H  

#include <Utility/IdentifierGenerator.h>  
#include <string>

namespace Engine {  

struct Resource  
{  
    enum class Type {  
    Texture, Shader, Sound, None  
    };  

    const std::string name;  
    const std::string path;  
    const Type type;  
    const Identifier id;

    Resource() : type(Type::None), id(-1), m_loaded(false) {}  

    Resource(const std::string& name, const std::string& path, Type type, Identifier id)  
    : name(name), path(path), type(type), id(id), m_loaded(false)
    {}  

    Resource(const Resource& other)  
        : name(other.name), path(other.path), type(other.type), id(other.id), m_loaded(other.m_loaded)
    {}  

    Resource& operator=(const Resource& other)  
    {  
        if (this != &other)  
        {  
            const_cast<std::string&>(name) = other.name;  
            const_cast<std::string&>(path) = other.path;  
            const_cast<Type&>(type) = other.type;  
            const_cast<Identifier&>(id) = other.id; 

            m_loaded = other.m_loaded;
        }  
        return *this;  
    }  

    Resource(Resource&& other) noexcept  
        : name(std::move(const_cast<std::string&>(other.name))), path(std::move(const_cast<std::string&>(other.path))),  
        type(other.type), id(other.id), m_loaded(other.m_loaded)
    {}  

    Resource& operator=(Resource&& other) noexcept  
    {  
        if (this != &other)  
        {  
            const_cast<std::string&>(name) = std::move(const_cast<std::string&>(other.name));  
            const_cast<std::string&>(path) = std::move(const_cast<std::string&>(other.path));  
            const_cast<Type&>(type) = other.type;  
            const_cast<Identifier&>(id) = other.id;  

            m_loaded = other.m_loaded;
        }  
        return *this;  
    }  

    virtual void unload() = 0;

protected:
    bool m_loaded;
};  

} // Engine  

#endif // !RESOURCE_H
