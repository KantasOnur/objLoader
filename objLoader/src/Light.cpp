#include "Light.hpp"

Light::Light(const glm::vec3& color)
: color_(color) 
{
    cube.setColor(glm::vec4(color, 1.0f));
}

void Light::transform(const glm::mat4 &transformation)
{
    cube.transform(transformation);
    modelMatrix = modelMatrix * transformation;
}

void Light::illuminate(const Shader& lampShader, const Shader& shader ,const Camera& camera)
{
    lampShader.Bind();
    position_ = modelMatrix * glm::vec4(position_, 1.0f);
    
    cube.draw(lampShader, camera.viewM_, camera.projectionM_);
    shader.Bind();
    shader.SetUniformVec3f("u_LightColor", color_);
    shader.SetUniformVec3f("u_LightPos", position_);
    shader.Unbind();
    
    modelMatrix = glm::mat4(1.0f);
}
/*
void Light::place(const Shader& shader, const glm::vec3& position)
{
    position_ = position;
    std::cout << glm::to_string(position_) << std::endl;
    
    shader.SetUniformVec3f("u_LightColor", color_);
    shader.SetUniformVec3f("u_LightPos", position_);
}
*/
