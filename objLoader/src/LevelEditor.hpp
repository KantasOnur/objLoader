#ifndef LevelEditor_hpp
#define LevelEditor_hpp

#include <stdio.h>
#include "Subject.hpp"
#include "Event.hpp"
#include "EventManager.hpp"
class LevelEditor
{
private:
    void onLevelEditEvent(const LevelEditorEvent& event);
    EventHandler<LevelEditorEvent> handler_;
    int index_;
public:
    LevelEditor();
};
#endif /* LevelEditor_hpp */
