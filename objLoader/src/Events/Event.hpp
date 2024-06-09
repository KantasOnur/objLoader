#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <glm/glm.hpp>

using namespace glm;

enum EventTypeIndex
{
    None, 
    KeyPressEvent, KeyReleaseEvent,
    MouseMoveEvent, MouseClickEvent
};

#define DEFINE_EVENT_TYPE(type)                                                           \
        static EventTypeIndex getStaticType() {return EventTypeIndex::type;}              \
        EventTypeIndex const getEventType() const override {return getStaticType();}      \


class Event
{
public:
    virtual const EventTypeIndex getEventType() const {return EventTypeIndex::None;}
    static const EventTypeIndex getStaticEventType() {return EventTypeIndex::None;}
    bool handled = false;
};


class KeyPressEvent : public Event
{
public:
    
    DEFINE_EVENT_TYPE(KeyPressEvent)

    int key_;
    KeyPressEvent(int key) : key_(key) {};
};

class KeyReleaseEvent : public Event
{
public:
    
    DEFINE_EVENT_TYPE(KeyReleaseEvent)
    
    int key_;
    KeyReleaseEvent(int key) : key_(key) {};


};


class MouseMoveEvent : public Event
{
public:
    
    DEFINE_EVENT_TYPE(MouseMoveEvent)
    
    int x_, y_;
    MouseMoveEvent(int x, int y) : x_(x), y_(y) {};
};

class MouseClickEvent : public Event
{
public:
    
    DEFINE_EVENT_TYPE(MouseClickEvent)
    
    int x_, y_, button_;
    MouseClickEvent(int x, int y, int button) : x_(x), y_(y), button_(button) {};
};
#endif /* Event_hpp */
