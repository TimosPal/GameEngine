#ifndef IWINDOW_H
#define IWINDOW_H

#include <string>

namespace Engine {

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual bool init() = 0;
    virtual void terminate() = 0;
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() = 0;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    std::string getTitle() const { return m_title; }
    bool isActive() const { return m_isActive; }

protected:
    IWindow(int width, int height, const std::string& title)
        : m_width(width), m_height(height), m_title(title), m_isActive(false)
    {
    }

    int m_width;
    int m_height;
    std::string m_title;

    bool m_isActive;
};

}

#endif