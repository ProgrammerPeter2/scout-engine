#pragma once
#include "Event.h"

namespace Scout {
    class SCOUT_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float mMouseX, float mMouseY) : m_MouseX(mMouseX), m_MouseY(mMouseY) {}

        inline float GetX() const {return m_MouseX;}
        inline float GetY() const {return m_MouseY;}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory)

    private:
        float m_MouseX, m_MouseY;
    };

    class SCOUT_API MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

        inline float GetXOffset() const {return m_XOffset;}
        inline float GetYOffset() const {return m_YOffset;}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory)

    private:
        float m_XOffset, m_YOffset;
    };


    class MouseButtonEvent: public Event {
    public:
        inline int GetButton() const {return m_Button;}

        EVENT_CLASS_CATEGORY(MouseButtonEventCategory | MouseEventCategory | InputEventCategory)
    protected:
        explicit MouseButtonEvent(int button) : m_Button(button) {}
        int m_Button;
    };

    class MouseButtonPressedEvent: public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressed: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent: public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleased: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}