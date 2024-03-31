cmake_minimum_required(VERSION 3.27)

project(scout)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(SC_PLATFORM_WINDOWS SC_BUILD_DLL)
add_library(scout SHARED Scout.h
        Scout/Core.h
        Scout/Application.cpp
        Scout/Application.h
        Scout/EntryPoint.h)
set_target_properties(scout PROPERTIES PUBLIC_HEADER Scout.h)
set_target_properties(scout PROPERTIES LINKER_LANGUAGE CXX)