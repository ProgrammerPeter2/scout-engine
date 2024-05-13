#include "GLWindow.h"
#include <iostream>
#include "../../Log.h"
#include "../../Events/ApplicationEvent.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"

static int windowCount;

Scout::GLWindow::GLWindow(Scout::WindowProps props)
    : Scout::Window(props), title(props.title) {
    if(windowCount == 0){
        if(!glfwInit()){
            Log::GetCoreLogger()->error("Failed to initialize glfw for {} window!", props.title);
            return;
        }
    }
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    this->window = glfwCreateWindow(this->width, this->height, props.title, NULL, NULL);
    windowCount++;
    glfwMakeContextCurrent(this->window);
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        Log::GetCoreLogger()->error("Failed to init glad for {} window!", props.title);
        return;
    }
    glfwSetWindowUserPointer(this->window, this);
    glfwSetWindowSizeCallback(this->window, [](GLFWwindow* window, int width, int height) {
        Scout::GLWindow& current_window = *(Scout::GLWindow*)glfwGetWindowUserPointer(window);
        current_window.width = width;
        current_window.height = height;
        Scout::WindowResizeEvent event(&current_window, width, height);
        current_window.event_callback(event);
    });
    glfwSetWindowCloseCallback(this->window, [](GLFWwindow* window) {
        Scout::GLWindow& current_window = *(Scout::GLWindow*)glfwGetWindowUserPointer(window);
        WindowCloseEvent close_event(&current_window);
        current_window.event_callback(close_event);
    });
    glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        Scout::GLWindow& current_window = *(Scout::GLWindow*)glfwGetWindowUserPointer(window);
        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent presse(&current_window, key, 0);
                current_window.event_callback(presse);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent revent(&current_window, key);
                current_window.event_callback(revent);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent repvent(&current_window, key, 1);
                current_window.event_callback(repvent);
                break;
            }
        }
    });
    glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods){
        Scout::GLWindow& current_window = *(Scout::GLWindow*)glfwGetWindowUserPointer(window);
        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(&current_window, button);
                current_window.event_callback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(&current_window, button);
                current_window.event_callback(event);
                break;
            }
        }
    });
    glfwSetScrollCallback(this->window, [](GLFWwindow* window, double xOffset, double yOffset){
        Scout::GLWindow& current_window = *(Scout::GLWindow*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent scroll(&current_window, (float)xOffset, (float)yOffset);
        current_window.event_callback(scroll);
    });
    glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double x, double y) {
        Scout::GLWindow& current_window = *(Scout::GLWindow*)glfwGetWindowUserPointer(window);
        MouseMovedEvent moved(&current_window, (float)x, (float)y);
        current_window.event_callback(moved);
    });
}

void Scout::GLWindow::close() {
    glfwMakeContextCurrent(NULL);
    Log::GetCoreLogger()->trace("Closing window {}", this->title);
    glfwDestroyWindow(this->window);
    windowCount--;
    this->window = nullptr;
    if(windowCount == 0) glfwTerminate();
}

void Scout::GLWindow::render() {
    if(glfwWindowShouldClose(this->window)) return;
    glfwMakeContextCurrent(this->window);
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

Scout::Window* Scout::Window::Create(Scout::WindowProps props) {
    return new Scout::GLWindow(props);
}
