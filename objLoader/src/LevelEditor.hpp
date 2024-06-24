#ifndef LevelEditor_hpp
#define LevelEditor_hpp

#include <stdio.h>
#include "Subject.hpp"
#include "Event.hpp"
#include "EventManager.hpp"

class LevelSubject : public Subject
{
public:
    LevelSubject(Shader* shader);
};

class LevelEditor
{
private:
    void onLevelEditEvent(const LevelEditorEvent& event);
    EventHandler<LevelEditorEvent> handler_;
    int index_;
    glm::vec3 firstClickCoords_;
public:
    LevelEditor();
};
#endif /* LevelEditor_hpp */
