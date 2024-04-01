cmake_minimum_required(VERSION 3.27)

project(hike)

set(CMAKE_CXX_STANDARD 17)
if (MSVC)
    add_compile_definitions(SC_PLATFORM_WINDOWS)
elseif (UNIX)
    add_compile_definitions(SC_PLATFORM_LINUX)
endif ()
add_executable(hike
        HikeApp.h
        HikeApp.cpp)
target_include_directories(hike PUBLIC "../scout")
target_link_libraries(hike scout)

if (MSVC)
    add_custom_command(TARGET hike POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/scout/scout.dll" "${CMAKE_CURRENT_BINARY_DIR}/scout.dll")
elseif (LINUX)
    add_custom_command(TARGET hike POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_BINARY_DIR}/scout/libscout.so" "${CMAKE_CURRENT_BINARY_DIR}/libscout.so")
elseif (APPLE)
    add_custom_command(TARGET hike POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_BINARY_DIR}/scout/libscout.dylib" "${CMAKE_CURRENT_BINARY_DIR}/libscout.dylib")
endif ()