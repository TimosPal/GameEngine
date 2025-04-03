#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include "Resource.h"

namespace Engine {

class TextureResource : public Resource {
public:
    TextureResource(const std::string& name, const std::string& filePath);
    ~TextureResource();

    void load() override;
    void unload() override;

    const unsigned char* getData() const { return m_data; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getChannels() const { return m_channels; }

private:
    std::string m_filePath;
    unsigned char* m_data;
    int m_width;
    int m_height;
    int m_channels;
};

} // Engine

#endif // TEXTURE_RESOURCE_H