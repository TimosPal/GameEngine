#ifndef SOURCE_CODE_RESOURCE_H
#define SOURCE_CODE_RESOURCE_H

#include "IResourceHandler.h"
#include <Utility/Util.h>

namespace Engine {

struct SourceCodeResource : public IResourceHandler
{
public:
    SourceCodeResource();
	SourceCodeResource(const std::string& name, const std::string& path);
    ~SourceCodeResource();

    void load() override;
    void unload() override;

    const std::string& getPath() { return m_path; }
    const std::string& getData();

private:
    std::string m_path;
    std::string m_data;
};

} // Engine

#endif // !SOURCE_CODE_RESOURCE_H
