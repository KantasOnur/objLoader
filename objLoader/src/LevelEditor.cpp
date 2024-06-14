#include "LevelEditor.hpp"
#include "ShaderManager.h"
#include "Scene.hpp"
LevelEditor::LevelEditor()
: handler_([this] (const LevelEditorEvent& event) {onLevelEditEvent(event);})
{
    std::unique_ptr<EventHandlerWrapper<LevelEditorEvent>> handler = std::make_unique<EventHandlerWrapper<LevelEditorEvent>>(handler_);
    
    EventManager::getInstance().sub(std::move(handler));
    
}

void LevelEditor::onLevelEditEvent(const LevelEditorEvent& event)
{
    if(event.firstClick_)
    {
        std::cout << "new object added" << std::endl;
        auto subjectPtr =  std::make_shared<Subject>(ShaderManager::getInstance().getShader("shaders/Basic.vert", "shaders/Basic.frag"));
        index_ = Scene::getInstance().addSubject(subjectPtr);
    }
    else
    {
        std::cout << index_ << std::endl;
        auto subjectPtr = Scene::getInstance().getSubject(index_);
        
    }
}
