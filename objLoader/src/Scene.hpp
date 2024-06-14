#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "Subject.hpp"
#include <glm/glm.hpp>

class Scene
{
private:
    Scene() {};
    std::vector<std::shared_ptr<Subject>> scene;
public:
    static Scene& getInstance()
    {
        static Scene scene;
        return scene;
    }
    
    int addSubject(std::shared_ptr<Subject> subject);
    std::shared_ptr<Subject> getSubject(int index);
    void drawScene(const glm::mat4& viewM, const glm::mat4& projectionM);
};
#endif /* Scene_hpp */
