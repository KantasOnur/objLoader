#ifndef EventManager_hpp
#define EventManager_hpp

#include <stdio.h>
#include "Event.hpp"
#include <memory>
#include <vector>
#include <iostream>

template <typename EventType>
using EventHandler = std::function<void(const EventType& event)>;



class EventHandlerWrapperInterface {
public:
    void Exec(const Event& e)
    {
        Call(e);
    }

    virtual std::string GetType() const = 0;
    virtual EventTypeIndex getEventType() const = 0;

private:
    virtual void Call(const Event& e) = 0;
};


template <typename EventType>
class EventHandlerWrapper : public EventHandlerWrapperInterface {
public:
    explicit EventHandlerWrapper(const EventHandler<EventType>& handler)
        : handler_(handler), handlerType_(handler.target_type().name()) {};
    
    EventTypeIndex getEventType() const override {return EventType::getStaticEventType();}

private:
    void Call(const Event& e) override
    {
       if (e.getEventType() == EventType::getStaticEventType()) {
           handler_(static_cast<const EventType&>(e));
        }
    }

    std::string GetType() const override { return handlerType_; }

    EventHandler<EventType> handler_;
    const std::string handlerType_;
};


class EventManager
{
public:
    
    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }
    
    void sub(std::unique_ptr<EventHandlerWrapperInterface>&& handler);
    void triggerEvent(Event& event);

    /*
    template <typename EventType>
    void unsub(const std::function<void(Event& event)>& handler);
    
    
    void queueEvent(Event& event);
    void dispatch();
    */
private:
    EventManager() {};
    std::vector<std::unique_ptr<Event>> queue_;
    std::unordered_map<EventTypeIndex, std::vector<std::unique_ptr<EventHandlerWrapperInterface>>> listeners_;
};

#endif /* EventManager_hpp */
