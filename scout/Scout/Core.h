#pragma once

#ifdef SC_PLATFORM_WINDOWS
    #ifdef SC_BUILD_DLL
        #define SCOUT_API __declspec(dllexport)
    #else
        #define SCOUT_API __declspec(dllimport)
    #endif
#endif
