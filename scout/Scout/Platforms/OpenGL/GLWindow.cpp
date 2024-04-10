#include "GLWindow.h"
#include <iostream>
#include "../../Log.h"
#include "../../Events/ApplicationEvent.h"

Scout::GLWindow::GLWindow(Scout::WindowProps props)
    : Scout::Window(props) {
    if(!glfwInit()){
        Log::GetCoreLogger()->error("Failed to initialize glfw for {} window!", props.title);
        return;
    }
    this->window = glfwCreateWindow(this->width, this->height, props.title, NULL, NULL);
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
        Scout::WindowResizeEvent event(width, height);
        current_window.event_callback(event);
    });
    glfwSetWindowCloseCallback(this->window, [](GLFWwindow* window) {
        WindowCloseEvent close_event;
        Scout::GLWindow& current_window = *(Scout::GLWindow*)glfwGetWindowUserPointer(window);
        current_window.event_callback(close_event);
    });
}

void Scout::GLWindow::close() {
    glfwDestroyWindow(this->window);
}

void Scout::GLWindow::render() {
    glfwMakeContextCurrent(this->window);
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

Scout::Window* Scout::Window::Create(Scout::WindowProps props) {
    return new Scout::GLWindow(props);
}
