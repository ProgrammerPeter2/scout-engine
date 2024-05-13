#pragma once

#ifdef SC_PLATFORM_WINDOWS
    #ifdef SC_BUILD_DLL
        #define SCOUT_API __declspec(dllexport)
    #else
        #define SCOUT_API __declspec(dllimport)
    #endif
#elif defined SC_PLATFORM_LINUX
    #ifdef SC_BUILD_DLL
        #define SCOUT_API __attribute__((dllexport))
    #else
        #define SCOUT_API __attribute__((dllimport))
    #endif
#elif defined SC_PLATFORM_MACOS
    #define SCOUT_API
#endif

#include <functional>
#define BIND_EVENT_FN(_class, method) std::bind(&_class::method, this, std::placeholders::_1)
#define BIND_STATIC_EVENT_FN(_class, method) std::bind(&_class::method, std::placeholders::_1)

