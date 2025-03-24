#ifndef RESOURCE_H  
#define RESOURCE_H  

#include <Utility/IdentifierGenerator.h>  
#include <string>

namespace Engine {  

struct Resource  
{  
public:
    enum class Type {  
    Texture, Shader, Sound, None  
    };

    Resource() : m_type(Type::None), m_id(-1), m_loaded(false) {}  

    Resource(const std::string& name, const std::string& path, Type type, Identifier id)  
    : m_name(name), m_path(path), m_type(type), m_id(id), m_loaded(false)
    {}  

    Resource(const Resource& other)  
        : m_name(other.m_name), m_path(other.m_path), m_type(other.m_type), m_id(other.m_id), m_loaded(other.m_loaded)
    {}  

    Resource& operator=(const Resource& other)  
    {  
        if (this != &other)  
        {  
            const_cast<std::string&>(m_name) = other.m_name;  
            const_cast<std::string&>(m_path) = other.m_path;  
            const_cast<Type&>(m_type) = other.m_type;  
            const_cast<Identifier&>(m_id) = other.m_id; 

            m_loaded = other.m_loaded;
        }  
        return *this;  
    }  

    Resource(Resource&& other) noexcept  
        : m_name(std::move(const_cast<std::string&>(other.m_name))), m_path(std::move(const_cast<std::string&>(other.m_path))),  
        m_type(other.m_type), m_id(other.m_id), m_loaded(other.m_loaded)
    {}  

    Resource& operator=(Resource&& other) noexcept  
    {  
        if (this != &other)  
        {  
            const_cast<std::string&>(m_name) = std::move(const_cast<std::string&>(other.m_name));  
            const_cast<std::string&>(m_path) = std::move(const_cast<std::string&>(other.m_path));  
            const_cast<Type&>(m_type) = other.m_type;  
            const_cast<Identifier&>(m_id) = other.m_id;  

            m_loaded = other.m_loaded;
        }  
        return *this;  
    }

    const std::string& getName() { return m_name; }
    const std::string& getPath() { return m_path; }
    const Type getType() { return m_type; }
    const Identifier getID() { return m_id; }

    virtual void unload() = 0;

protected:
    virtual void load() = 0;

    bool m_loaded;

    const std::string m_name;
    const std::string m_path;
    const Type m_type;
    const Identifier m_id;
};  

} // Engine  

#endif // !RESOURCE_H
