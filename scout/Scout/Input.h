#pragma once
#include "Core.h"
#include <list>
#include "Events/Event.h"

namespace Scout {
    class SCOUT_API Input{
    public:
        static void HandleInputEvent(Event& event);
        static bool GetKey(int key);
        static bool GetMouseButton(int button);

        struct MouseData {
            float x;
            float y;
        };

        static MouseData GetMousePos();
    private:
        static std::list<int> keys;
        static std::list<int> mouse_buttons;
        static MouseData mouseInfo;
    };
}