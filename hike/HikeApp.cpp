#include "HikeApp.h"
#include <iostream>

void HikeApp::Run() {
    Scout::Log::GetClientLogger()->trace("Hello from Hike!");
}

Scout::Application* Scout::CreateApplication() {
    return new HikeApp();
}
