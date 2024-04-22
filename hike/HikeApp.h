#pragma once
#include <Scout.h>

class HikeApp: public Scout::Application {
public:
    HikeApp();
    void Run() override;
private:
    Scout::Window* root_window;
    Scout::Window* sub_window;
    bool running = true;
    bool sub_render = true;
    void MainWindowClosed(Scout::Event& event);
    void SubWindowClosed(Scout::Event& event);
};