#include "EventManager.hpp"

template <typename EventType>
void EventManager::sub(const EventHandler<EventType> &handler)
{
    EventTypeIndex index = EventType::getStaticType();
    auto handlers = listeners_.find(index);
    if(handlers != listeners_.end())
    {
        auto& callbacks = handlers->second;
        for(auto& it : callbacks)
        {
            if(handler.getType() == it.getType())
            {
                std::cout << "callback already exists for :" << index << std::endl;
            }
        }
        callbacks.emplace_back(handler);
    }
    else
    {
        listeners_[index].emplace_back(handler);
    }
}

template <typename EventType>
void EventManager::unsub(const std::function<void(Event& event)>& handler)
{
    EventTypeIndex index = EventType::getStaticType();
    std::string handlerName = handler.target_type().name();
    
    auto& handlers = listeners_[index];
    for(auto it = handlers.begin(); it != handlers.end(); it++)
    {
        if(it->getType() == handlerName)
        {
            it = handlers.erase(it);
            return;
        }
    }
}

void EventManager::triggerEvent(Event& event)
{
    for(auto& handler : listeners_[event.getEventType()])
    {
        handler.Call(event);
    }
}

void EventManager::queueEvent(Event& event)
{
    std::unique_ptr<Event> eventPtr = std::make_unique<Event>(event);
    
    queue_.emplace_back(std::move(eventPtr));
}

void EventManager::dispatch()
{
    for(auto it = queue_.begin(); it != queue_.end();)
    {
        if(!it->get()->handled)
        {
            triggerEvent(*it->get());
            it = queue_.erase(it);
        }
        else
        {
            it++;
        }
    }
}

