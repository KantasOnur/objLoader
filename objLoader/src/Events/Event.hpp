#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <glm/glm.hpp>

enum EventTypeIndex
{
    None, 
    KeyPress, KeyRelease,
    MouseMove, MouseClick,
    LevelEdit
};

#define DEFINE_EVENT_TYPE(type)                                                                     \
        static EventTypeIndex getStaticEventType() {return EventTypeIndex::type;}                   \
        EventTypeIndex const getEventType() const override {return getStaticEventType();}           \


class Event
{
public:
    virtual const EventTypeIndex getEventType() const {return EventTypeIndex::None;}
    //static const EventTypeIndex getStaticEventType() {return EventTypeIndex::None;}
    bool handled = false;
};


class KeyPressEvent : public Event
{
public:
    
    DEFINE_EVENT_TYPE(KeyPress)

    int key_;
    KeyPressEvent(int key) : key_(key) {};
};

class KeyReleaseEvent : public Event
{
public:
    
    DEFINE_EVENT_TYPE(KeyRelease)
    
    int key_;
    KeyReleaseEvent(int key) : key_(key) {};


};


class MouseMoveEvent : public Event
{
public:
    
    DEFINE_EVENT_TYPE(MouseMove)
    
    int x_, y_;
    MouseMoveEvent(int x, int y) : x_(x), y_(y) {};
};

class MouseClickEvent : public Event
{
public:
    
    DEFINE_EVENT_TYPE(MouseClick)
    
    int x_, y_, button_;
    MouseClickEvent(int x, int y, int button) : x_(x), y_(y), button_(button) {};
};

class LevelEditorEvent: public Event
{
public:
    DEFINE_EVENT_TYPE(LevelEdit)
    
    int x_, y_;
    glm::vec3 worldCoords_;
    bool firstClick_;
    LevelEditorEvent(int x, int y, glm::vec3 coords) : x_(x), y_(y), worldCoords_(coords) {};
};
#endif /* Event_hpp */
