#pragma once

#include <functional>
#include "Core.h"
#include "Events/Event.h"

namespace Scout {
    struct SCOUT_API WindowProps {
        int width, height;
        char *title;
        std::function<void(Event&)> event_callback;
    };


    class SCOUT_API Window {
    public:
        virtual void close() = 0;
        virtual void render() = 0;

        static Window* Create(WindowProps props);
    protected:
        int width, height;
        std::function<void(Event&)> event_callback;
        Window(WindowProps props)
            : width(props.width), height(props.height), event_callback(props.event_callback) {}

    };
}
