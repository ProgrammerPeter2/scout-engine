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