#include "Application.h"
#include "Log.h"
#include "Input.h"

namespace Scout {
    Application::Application() {
        this->dispatcher.AddEventHandler(new EventTypeFilter(EventType::WindowClosed),
                                         BIND_EVENT_FN(Application, OnWindowClose));
        this->dispatcher.AddEventHandler(new EventCategoryFilter(EventCategory::InputEventCategory),
                                         BIND_STATIC_EVENT_FN(Input, HandleInputEvent));
    }

    Application::~Application() {}

    void Application::Run() {
        while (true);
    }

    Window *Application::new_window(int width, int height, char* title) {
        return Window::Create(WindowProps{width, height, title,
                                          BIND_EVENT_FN(Application, OnEvent)});
    }

    void Application::OnEvent(Event &event) {
        this->dispatcher.HandleEvent(event);
    }

    void Application::OnWindowClose(Event &event) {
        if(event.GetEventType() != EventType::WindowClosed) return;
        event.GetEventWindow()->close();
        Log::GetCoreLogger()->trace("Window close!");
    }
} // Scout