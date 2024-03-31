cmake_minimum_required(VERSION 3.27)

project(hike)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(SC_PLATFORM_WINDOWS)
add_executable(hike
        HikeApp.h
        HikeApp.cpp)
target_include_directories(hike PUBLIC "../scout")
target_link_libraries(hike scout)
add_custom_command(TARGET hike POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/scout/scout.dll" "${CMAKE_CURRENT_BINARY_DIR}/scout.dll")