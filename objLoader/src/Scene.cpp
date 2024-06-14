#include "Scene.hpp"

int Scene::addSubject(std::shared_ptr<Subject> subject)
{
    scene.emplace_back(subject);
    return scene.size() - 1;
}

std::shared_ptr<Subject> Scene::getSubject(int index)
{
    return scene[index];
}

void Scene::drawScene(const glm::mat4& viewM, const glm::mat4& projectionM)
{
    for(auto& subject : scene)
    {
        subject->draw(viewM, projectionM);
    }
}
