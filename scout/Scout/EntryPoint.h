#pragma once
#include "Application.h"
#include <iostream>
extern Scout::Application* Scout::CreateApplication();

int main(int argc, char** argv){
    auto app = Scout::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
