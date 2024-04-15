#pragma once
#include "Event.h"
#include <map>
#include <list>
#include <functional>

namespace Scout {
    class SCOUT_API EventFilter {
    public:
        virtual bool applyFilter(Event& event) = 0;
    };

    class SCOUT_API EventTypeFilter: public EventFilter {
    public:
        explicit EventTypeFilter(EventType eventType) : eventType(eventType) {}
        bool applyFilter(Event &event) override {
            return event.GetEventType() == eventType;
        }
    private:
        EventType eventType;
    };

    class SCOUT_API EventCategoryFilter: public EventFilter {
    public:
        explicit EventCategoryFilter(EventCategory category) : category(category) {}
        bool applyFilter(Event &event) override {
            return event.IsInCategory(category);
        }
    private:
        EventCategory category;
    };

    class SCOUT_API EventDispatcher {
    public:
        void AddEventHandler(EventFilter* filter, std::function<void(Event&)> method) {
            // Step 1: find filter as a key
            if (event_handlers.find(filter) != event_handlers.end()) {
                // Step 2a: add method to the list of the filter, if the filter is present
                event_handlers[filter].push_back(method);
            } else {
                // Step 2b: otherwise, init a new list with the method and set a filter as a new map
                std::list<std::function<void(Event&)>> handlers {method};
                event_handlers[filter] = handlers;
            }
        };
        void HandleEvent(Event& event) {
            for(const auto& [filter, handlers] : event_handlers) {
                if (!filter->applyFilter(event)) continue;
                for (const auto& handler : handlers) {
                    handler(event);
                }
            }
        };
    private:
        std::map<EventFilter*, std::list<std::function<void(Event&)>>> event_handlers;
    };
}