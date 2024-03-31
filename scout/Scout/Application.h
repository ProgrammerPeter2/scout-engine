#pragma once
#include "Core.h"

namespace Scout {

    class SCOUT_API Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();
    };

    SCOUT_API Application* CreateApplication();
} // Scout