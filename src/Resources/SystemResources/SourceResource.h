#ifndef SOURCE_RESOURCE_H
#define SOURCE_RESOURCE_H

#include "IResource.h"
#include <Utility/Util.h>

namespace Engine {

struct SourceResource : public IResource
{
public:
    SourceResource();
    SourceResource(const std::string& path);

    bool init() override;
    void destroy() override;

    const std::string& getPath() { return m_path; }
    const std::string& getData() { return m_data; }

private:
    std::string m_path;
    std::string m_data;
};

} // Engine

#endif // !SOURCE_RESOURCE_H
