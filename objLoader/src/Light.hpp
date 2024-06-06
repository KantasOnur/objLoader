#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <glm.hpp>
#include "Shader.hpp"
#include "Camera.hpp"
#include "Cube.hpp"

class Light
{
public:
    glm::vec3 color_;
    glm::vec3 position_ = {0.0f, 0.0f, 0.0f};
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    
    Cube cube;
public:
    Light(const glm::vec3& color = {1.0f, 1.0f, 1.0f});
    void transform(const glm::mat4& transformation);
    void illuminate(const Shader& shader, const Shader& lampShader , const Camera& camera);
    //void place(const Shader& shader, const glm::vec3& position);
};

#endif /* Light_hpp */
