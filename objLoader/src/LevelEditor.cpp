#define GLM_ENABLE_EXPERIMENTAL


#include "LevelEditor.hpp"
#include "ShaderManager.h"
#include "Scene.hpp"
#include "Cube.hpp"
#include "glm/gtx/transform.hpp"

LevelSubject::LevelSubject(Shader* shader) : Subject(shader)
{
    data_ = std::vector<Layout>(4);
    indices_ = {
        0, 1, 2,
        2, 3, 1
    };
    updateVertices();
}

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
        std::shared_ptr<LevelSubject> subject = std::make_shared<LevelSubject>(GET_SHADER(Basic));
        subject->updateVertex(event.worldCoords_, 0);
        
        index_ = Scene::getInstance().addSubject(subject);
    }
    else
    {
        std::cout << index_ << std::endl;
        auto subjectPtr = Scene::getInstance().getSubject(index_);
        
        glm::vec3 p1 = subjectPtr->getVertex(0) + glm::vec3(0.0f, 0.0f, event.worldCoords_.z);
        glm::vec3 p2 = subjectPtr->getVertex(0) + glm::vec3(event.worldCoords_.x, 0.0f, 0.0f);
        glm::vec3 p3 = subjectPtr->getVertex(0) + glm::vec3(event.worldCoords_.x, 0.0f, event.worldCoords_.z);
        
        subjectPtr->updateVertex(p1, 1);
        subjectPtr->updateVertex(p2, 2);
        subjectPtr->updateVertex(p3, 3);
    }
}
