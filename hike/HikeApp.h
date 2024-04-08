#pragma once
#include <Scout.h>

class HikeApp: public Scout::Application {
public:
    HikeApp();
    void Run() override;
    void OnEvent(Scout::Event& event) override;
private:
    Scout::Window* window;
    bool running = true;
};