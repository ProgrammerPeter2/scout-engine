#pragma once

#include "Event.h"

namespace Scout {
    class SCOUT_API WindowResizeEvent: public Event{
    private:
        unsigned int m_Width, m_Height;
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {};

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Window Resize Event: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResized);
        EVENT_CLASS_CATEGORY(ApplicationEventCategory);

    };

    class SCOUT_API WindowCloseEvent: public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClosed)

        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
    };
}