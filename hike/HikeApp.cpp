#include "HikeApp.h"
#include <iostream>

void HikeApp::Run() {
     std::cout << "Welcome to Scout Engine!" << std::endl;
}

Scout::Application* Scout::CreateApplication() {
    return new HikeApp();
}
