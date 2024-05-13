#pragma once
#include "Window.h"
#include "Core.h"
#include "Events/Event.h"
#include "Events/EventDispatcher.h"

namespace Scout {
    class SCOUT_API Application {
    public:
        Application();
        virtual ~Application();
        virtual void Run();
    protected:
        Window* new_window(int width, int height, char* title);
        EventDispatcher dispatcher;
        void OnEvent(Event& event);
        void OnWindowClose( Event& event);
    };

    SCOUT_API Application* CreateApplication();
} // Scout