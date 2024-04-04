#pragma once
#include "Event.h"


namespace Scout {
    class SCOUT_API KeyEvent: public Event {
    public:
        inline int GetKey() const { return m_key; }

        EVENT_CLASS_CATEGORY(KeyEventCategory | InputEventCategory)

    protected:
        KeyEvent(int key)
            : m_key(key) {};

        int m_key;
    };

    class SCOUT_API KeyPressedEvent: public KeyEvent {
    public:
        KeyPressedEvent(int key, int repeats)
            : KeyEvent(key), m_Repeats(repeats) {};

        inline int GetRepeatCount() const { return m_Repeats; };

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressed: " << m_key << " (" << m_Repeats << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_Repeats;
    };

    class SCOUT_API KeyReleasedEvent: public KeyEvent {
    public:
        KeyReleasedEvent(int key)
            : KeyEvent(key) {};

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleased: " << m_key;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}