#ifndef EventManager_hpp
#define EventManager_hpp

#include <stdio.h>
#include "Event.hpp"
#include "EventHandler.h"
#include <memory>
#include <vector>
#include <iostream>

class EventManager
{
public:
    template <typename EventType>
    void sub(const EventHandler<EventType>& handler);
    
    template <typename EventType>
    void unsub(const std::function<void(Event& event)>& handler);
    
    void triggerEvent(Event& event);
    
    void queueEvent(Event& event);
    void dispatch();
    
private:
    
    std::vector<std::unique_ptr<Event>> queue_;
    std::unordered_map<EventTypeIndex, std::vector<EventHandlerInterface>> listeners_;
};

#endif /* EventManager_hpp */
