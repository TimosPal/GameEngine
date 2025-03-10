#ifndef IWINDOW_H
#define IWINDOW_H

#include <string>

namespace Engine {

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual bool Init() = 0;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height;}
    std::string getTitle() const { return m_title; }

protected:
    IWindow(int width, int height, const std::string& title)
        : m_width(width), m_height(height), m_title(title)
    {}

    int m_width;
    int m_height;
    std::string m_title;
};

}

#endif