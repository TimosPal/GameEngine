#include "TextureResource.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Engine {

TextureResource::TextureResource()
    : TextureResource("", "")
{}

TextureResource::TextureResource(const std::string& name, const std::string& filePath)
    : m_filePath(filePath), m_width(0), m_height(0), m_channels(0), m_data(nullptr)
{}

bool TextureResource::init()
{
    LOG_INFO("Loading texture : {}", m_filePath);

    stbi_set_flip_vertically_on_load(true);
    m_data = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_channels, 0);
    if (!m_data) {
        LOG_ERROR("Failed to load texture: {}", m_filePath);
        return false;
    }

    return true;
}

void TextureResource::destroy()
{
    if (m_data) 
    {
        LOG_INFO("Unloading texture : {}", m_filePath);

        stbi_image_free(m_data);
        m_data = nullptr;
        m_width = m_height = m_channels = 0;
    }
}

} // Engine