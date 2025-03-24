#ifndef SHADER_RESOURCE_H
#define SHADER_RESOURCE_H

#include "Resource.h"
#include <Utility/Util.h>

namespace Engine {

struct ShaderResource : public Resource
{
    ShaderResource();
    ShaderResource(const std::string& name, const std::string& path);
    ShaderResource(const ShaderResource& other);
    ShaderResource& operator=(const ShaderResource& other);
    ShaderResource(ShaderResource&& other) noexcept;
    ShaderResource& operator=(ShaderResource&& other) noexcept;

    std::string getString();
    void unload();

private:
    std::string m_data;
};

} // Engine

#endif // !SHADER_RESOURCE_H
