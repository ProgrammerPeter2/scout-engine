#pragma once
#include "Application.h"
#include "Log.h"
#include <iostream>

extern Scout::Application* Scout::CreateApplication();

int main(int argc, char** argv){
    Scout::Log::Init();
    Scout::Log::GetCoreLogger()->trace("Log from Scout Start!");
    auto app = Scout::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
