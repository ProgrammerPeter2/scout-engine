#pragma once
#include "../Core.h"
#include <string>
#include <sstream>

#define BIT(x) 1 << x

namespace Scout {
    /**
 *  Enum for categorizing different events.
 */
    enum EventCategory {
        ApplicationEventCategory = BIT(0),
        InputEventCategory = BIT(1),
        KeyEventCategory = BIT(2),
        MouseEventCategory = BIT(3),
        MouseButtonEventCategory = BIT(4),
        // UI events
        // Network events
    };

    enum class EventType {
        WindowResized, WindowClosed, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }

    class SCOUT_API Event {
    public:
        virtual ~Event() = default;
        bool handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & category;
        }
    };
}