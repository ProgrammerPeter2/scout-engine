//
// Created by hpras on 2024. 03. 31..
//

#include "Application.h"

namespace Scout {
    Application::Application() {
    }

    Application::~Application() {}

    void Application::Run() {
        while (true);
    }

    Window *Application::new_window(int width, int height, char* title) {
        return Window::Create(WindowProps{width, height, title, BIND_EVENT_FN(EventHandle)});
    }

    void Application::EventHandle(Event &event) {
        this->OnEvent(event);
    }
} // Scout