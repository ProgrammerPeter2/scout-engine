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
}

void HikeApp::OnEvent(Scout::Event& event) {
    if(event.GetEventType() == Scout::EventType::WindowClosed) {
        Scout::Log::GetClientLogger()->trace("Closing!");
        this->running = false;
    }
    Scout::Log::GetClientLogger()->trace(event.ToString());
}


Scout::Application* Scout::CreateApplication() {
    return new HikeApp();
}
