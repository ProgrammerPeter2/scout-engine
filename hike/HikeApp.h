#pragma once
#include <Scout.h>

class HikeApp: public Scout::Application {
public:
    HikeApp();
    void Run() override;
private:
    Scout::Window* window;
    bool running = true;
    void WindowClosed(Scout::Event& event);
};