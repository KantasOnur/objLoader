#ifndef EventHandler_h
#define EventHandler_h

#include <string>
#include "Event.hpp"

class EventHandlerInterface
{
private:
    virtual void Exec(const Event& event) = 0;
public:
    virtual void Call(const Event& event) {Exec(event);}
    virtual std::string getType() = 0;
};

template <typename EventType>
class EventHandler : public EventHandlerInterface
{
private:
    std::function<void(Event& event)> handler_;
    std::string type_;
    void Exec(const Event& event) override {handler_(event);}
public:
    EventHandler(std::function<void(EventType& event)> handler)
    : handler_(handler), type_(handler.target_type().name()) {};
    std::string getType() override {return type_;}
};

#endif /* EventHandler_h */
