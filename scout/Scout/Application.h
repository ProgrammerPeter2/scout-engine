#pragma once
#include "Window.h"
#include "Core.h"
#include "Events/Event.h"
#include <functional>
#define BIND_EVENT_FN(method) std::bind(&Application::method, this, std::placeholders::_1)

namespace Scout {

    class SCOUT_API Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();
        virtual void OnEvent(Event& event) = 0;
    protected:
        Window* new_window(int width, int height, char* title);
        void EventHandle(Event& event);
    };

    SCOUT_API Application* CreateApplication();
} // Scout