#include "EventManager.hpp"

#define LOG(x) \
        std::cout << x << std::endl;

void EventManager::sub(std::unique_ptr<EventHandlerWrapperInterface>&& handler)
{
    
    EventTypeIndex type = handler->getEventType();
    LOG(type)
    
    auto listeners = listeners_.find(type);
    if(listeners != listeners_.end())
    {
        auto& callbacks = listeners->second;
        for(auto& it : callbacks)
        {
            if(handler->GetType() == it->GetType())
            {
                LOG("Attempted to sub identical callback.")
                return;
            }
        }
        callbacks.emplace_back(std::move(handler));
    }
    else
    {
        listeners_[type].emplace_back(std::move(handler));
    }
     
}

void EventManager::triggerEvent(Event& event)
{
    EventTypeIndex type = event.getEventType();
    
    for(auto& handlers : listeners_[type])
    {
        handlers->Exec(event);
    }
}

/*
void EventManager::sub(EventTypeIndex type, EventHandler& handler)
{
    auto listeners = listeners_.find(type);
    if(listeners != listeners_.end())
    {
        auto& callbacks = listeners->second;
        for(auto& it : callbacks)
        {
            if(handler.target_type().name() == it.target_type().name())
            {
                std::cout << "callback already exists for : " << type << std::endl;

                return;
            }
        }
        callbacks.emplace_back(std::move(handler));
    }
    else
    {
        std::cout << handler.target_type().name() << std::endl;
        listeners_[type].emplace_back(std::move(handler));
        std::cout << type << std::endl;
        
        if(handler)
        {
            std::cout << "here" << std::endl;
        }
        else
        {
            std::cout << "there" << std::endl;
        }
    }
}


void EventManager::triggerEvent(Event& event)
{
    listeners_[MouseClickEvent::getStaticType()][0](event);
}

*/
/*
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

*/
