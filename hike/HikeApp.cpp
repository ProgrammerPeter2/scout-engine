#include "HikeApp.h"
#include <iostream>

void HikeApp::Run() {
    Scout::Log::GetClientLogger()->trace("Hello from Hike!");
    while(this->running){
        this->window->render();
    }
}

HikeApp::HikeApp() {
    this->window = this->new_window(1280, 720, "Hike");
    this->dispatcher.AddEventHandler(new Scout::EventTypeFilter(Scout::EventType::WindowClosed),
                                     BIND_EVENT_FN(HikeApp, WindowClosed));
}

void HikeApp::WindowClosed(Scout::Event &event) {
    if(event.GetEventType() != Scout::EventType::WindowClosed) return;
    this->running = false;
}

Scout::Application* Scout::CreateApplication() {
    return new HikeApp();
}