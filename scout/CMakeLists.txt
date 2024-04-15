cmake_minimum_required(VERSION 3.27)

project(scout)

set(CMAKE_CXX_STANDARD 17)
if (APPLE)
    set(CMAKE_CXX_VISIBILITY_PRESET default)
    set(CMAKE_VISIBILITY_INLINES_HIDDEN 0)
endif ()

if (MSVC)
    add_compile_definitions(SC_PLATFORM_WINDOWS SC_BUILD_DLL)
elseif (LINUX)
    add_compile_definitions(SC_PLATFORM_LINUX SC_BUILD_DLL)
elseif (APPLE)
    add_compile_definitions(SC_PLATFORM_MACOS)
endif ()
add_subdirectory(vendor)
add_library(scout SHARED Scout.h
        Scout/Core.h
        Scout/Application.cpp
        Scout/Application.h
        Scout/EntryPoint.h
        Scout/Log.cpp
        Scout/Log.h
        Scout/Events/Event.h
        Scout/Events/ApplicationEvent.h
        Scout/Events/KeyEvent.h
        Scout/Events/MouseEvent.h
        Scout/Window.h
        Scout/Platforms/platform.h
        Scout/Platforms/OpenGL/GLWindow.cpp
        Scout/Platforms/OpenGL/GLWindow.h
        Scout/Events/EventDispatcher.h)
target_include_directories(scout PUBLIC vendor/spdlog/include vendor/glfw/include vendor/glad)
target_link_libraries(scout PUBLIC ${OPENGL_LIBRARIES} glfw glad)
set_target_properties(scout PROPERTIES PUBLIC_HEADER Scout.h)
set_target_properties(scout PROPERTIES LINKER_LANGUAGE CXX)