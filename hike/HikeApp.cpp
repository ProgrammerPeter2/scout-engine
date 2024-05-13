#include "HikeApp.h"
#include <iostream>

void HikeApp::Run() {
    Scout::Log::GetClientLogger()->trace("Hello from Hike!");
    while(this->running){
        if(Scout::Input::GetKey(SC_KEY_LEFT_CONTROL))
            Scout::Log::GetCoreLogger()->trace("mouse: {}; {}", Scout::Input::GetMousePos().x, Scout::Input::GetMousePos().y);
        this->root_window->render();
        if(this->sub_render) this->sub_window->render();
    }
}

HikeApp::HikeApp() {
    this->root_window = this->new_window(1280, 720, "Hike");
    this->sub_window = this->new_window(500, 500, "Hike Sub");
    this->dispatcher.AddEventHandler(new Scout::EventTypeFilter(Scout::EventType::WindowClosed, this->root_window),
                                     BIND_EVENT_FN(HikeApp, MainWindowClosed));
    this->dispatcher.AddEventHandler(new Scout::EventTypeFilter(Scout::EventType::WindowClosed, this->sub_window),
                                     BIND_EVENT_FN(HikeApp, SubWindowClosed));
}

void HikeApp::MainWindowClosed(Scout::Event &event) {
    if(event.GetEventType() != Scout::EventType::WindowClosed) return;
    this->running = false;
}

void HikeApp::SubWindowClosed(Scout::Event &event) {
    if(event.GetEventType() != Scout::EventType::WindowClosed) return;
    if(event.GetEventWindow() == this->sub_window) {
        this->sub_render = false;
    }
}

Scout::Application* Scout::CreateApplication() {
    return new HikeApp();
}