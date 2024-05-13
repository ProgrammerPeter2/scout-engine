#include "Input.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Log.h"

std::list<int> Scout::Input::keys = std::list<int>();
std::list<int> Scout::Input::mouse_buttons = std::list<int>();
Scout::Input::MouseData Scout::Input::mouseInfo = MouseData{0, 0};

bool list_contains_int(std::list<int>* list, int number) {
    for (const int &item: *list) {
        if(number == item) return true;
    }
    return false;
}

void Scout::Input::HandleInputEvent(Scout::Event &event) {
    if(!event.IsInCategory(EventCategory::InputEventCategory)) return;
    if(event.IsInCategory(EventCategory::KeyEventCategory)) {
        int key = ((KeyEvent&)event).GetKey();
        switch (event.GetEventType()) {
            case Scout::EventType::KeyPressed: {
                if (!list_contains_int(&Input::keys, key)) Input::keys.push_back(key);
                break;
            }
            case Scout::EventType::KeyReleased: {
                if(list_contains_int(&Input::keys, key)) Input::keys.remove(key);
                break;
            }
            default:
                break;
        }
    }else if(event.IsInCategory(Scout::EventCategory::MouseEventCategory)){
        switch (event.GetEventType()) {
            case Scout::EventType::MouseMoved: {
                auto &moveEvent = (MouseMovedEvent &) event;
                Input::mouseInfo = MouseData{moveEvent.GetX(), moveEvent.GetY()};
                break;
            }
            case Scout::EventType::MouseButtonPressed: {
                int button = ((MouseButtonEvent&)event).GetButton();
                if(!list_contains_int(&Input::mouse_buttons, button)) Input::mouse_buttons.push_back(button);
                break;
            }
            case Scout::EventType::MouseButtonReleased: {
                int button = ((MouseButtonEvent&)event).GetButton();
                if(list_contains_int(&Input::mouse_buttons, button)) Input::mouse_buttons.remove(button);
                break;
            }
            default:
                break;
        }
    }
}

bool Scout::Input::GetKey(int key) {
    return list_contains_int(&Input::keys, key);
}

bool Scout::Input::GetMouseButton(int button) {
    return list_contains_int(&Input::mouse_buttons, button);
}

Scout::Input::MouseData Scout::Input::GetMousePos() {
    return Scout::Input::mouseInfo;
}
