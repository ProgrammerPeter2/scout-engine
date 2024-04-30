# Scout

The Engine itself.

## A simple example
To create a scout app you need nothing else, but to create a scout application.
Here is a simple example by doing that:
```c++
//file: sample_app.h
#pragma once
#include <Scout.h>

class SampleApp: public Scout::Application{
    void Run() override;
};
```
```c++
//file: sample_app.cpp
#include "sample_app.h"
#include <iostream> // just for to make this example work

void SampleApp::Run(){
    std::cout << "Hello from a Scout Application!" << std::endl;
}

// this function returns an instance of our scout app
Scout::Application* Scout::CreateApplication(){
    return new SampleApp();
}
```

## Logging
Scout Engine uses [spdlog](https://github.com/gabime/spdlog) for logging,
and the engine itself only creates the loggers that you can use in the usual way.
To access the loggers you can call `Scout::Log::GetClientLogger` and you are in business.
Here is an updated version of the example app that uses our logging "system":
```c++
// file: sample_app.h
// Nothing changed at all!
```
```c++
// file: sample_app.cpp
#pragma once
#include "sample_app.h"

void SampleApp::Run(){
    Scout::Log::GetClientLogger()->trace("Hello from the client logger!");
}

// and Scout::CreateApplication is the same
```

## Windowing
Scout Engine provides powerful windowing management feature.
It lets you create, destroy and call the render function in a way you want.

To create a window use `Application::new_window` (call it only from your app implementation).
Pass it a width, height and the title and it will return a window pointer.
For render call `Window::render()` and for destroy this object use `Window::close()`.

### Events
During runtime, users can fire different events by interacting your application.
We have the following events implementing the base `Event` class:
 - **ApplicationEventCategory** like `WindowResize(int width, int height)`, `WindowClose` (note that these are the actually implemented events in this category)
 - **InputEventCategory** for all the input events
   - **KeyEventCategory**: `KeyPressed(int key)`, `KeyReleased(int key)`
   - **MouseEventCategory**: `MouseMoved(float x, float y)`, `MouseScrolled(float x, float y)`
     - **MouseButtonEventCategory**: `MouseButtonPressed(int key)`, `MouseButtonReleased(int key)`

All events contain the window where they were fired.

#### Handling those events
Your application has an event dispatcher, where you can register your event handlers using the `AddEventHandler` method.
You have to provide a filter and a callback method to call. A filter can be an event category or event type filter and you can also filter for the window where it was fired.
To provide the callback use the `BIND_EVENT_FN` (or `BIND_STATIC_EVENT_FN` - WIP).

When an event happened, the source window will call the dispatcher's `HandleEvent` method. You can use it for your own ideas too.

### A minimal multi-window application
At the end of the day though not really much changed. You just need to create an application with 1 (or more) windows and create a "run-loop" for it.
If you want you can also subscribe for events with your custom event processors to interact with users.

But first, you'll need a header for your application:
```c++
//file: sample_window_app.h
#pragma once
#include <Scout.h>

// your application class
class WindowApp: public Scout::Application {
public:
    WindowApp(); // we need it for setup
    void Run() override;
private:
    // everything needed for control
    Scout::Window* window1;
    Scout::Window* window2;
    bool running = false;
    // event handlers
    void OnWindowClose(Event& event);
    void OnSecondInput(Event& event); // should be called when an input event is fired from the second window
};
```
Second, implement these methods. 
```c++
//file: sample_window_app.c
#include <sample_window_app.h>

///// PUBLIC METHODS /////

WindowApp::WindowApp(){
    // init the two window
    this->window1 = this->new_window(576, 256, "Window 1");
    this->window2 = this->new_window(480, 640, "Window 2");
    // register the event handlers
    this->dispatcher.AddEventHandler(new Scout::EventTypeFilter(Scout::EventType::WindowClosed), BIND_EVENT_FN(WindowApp, OnWindowClose)); // registered `OnWindowClose` method as a window close event handler
    this->dispatcher.AddEventHandler(new Scout::EventCategoryFilter(Scout::EventCategory::InputEventCategory, this->window2),
                BIND_EVENT_FN(WindowApp, OnSecondInput)); // registered `OnSecondInput` method as an input category event handler but only for `window2`
}

// just render the two windows until the app is running
void WindowApp::Run() {
    while(this->running){
        this->window1->render();
        this->window2->render();
    }
}

///// PRIVATE METHODS /////

// close the app when a window is closed
void WindowApp::OnWindowClose(Event& event){
    if(event.GetEventType() != Scout::EventType::WindowClosed) return; // type check for safety
    this->running = false;
}

// print the received event with extra formatting
void WindowApp::OnSecondInput(Event& event){
    if(!event.IsInCategory(Scout::EventCategory::InputEventCategory)) return; // category check
    if(event.IsInCategory(Scout::EventCategory::KeyEventCategory))
        Scout::Log::GetClientLogger()->trace("This is a key event!");
    if(event.GetEventType() == Scout::EventType::MouseMoved)
        Scout::Log::GetClientLogger()->trace(event.ToString());
}
```
