#ifndef SOURCE_HANDLER_H
#define SOURCE_HANDLER_H

#include "IResourceHandler.h"
#include <Utility/Util.h>

namespace Engine {

struct SourceHandler : public IResourceHandler
{
public:
    SourceHandler();
    SourceHandler(const std::string& name, const std::string& path);
    ~SourceHandler();

    void load() override;
    void unload() override;

    const std::string& getPath() { return m_path; }
    const std::string& getData();

private:
    std::string m_path;
    std::string m_data;
};

} // Engine

#endif // !SOURCE_HANDLER_H
