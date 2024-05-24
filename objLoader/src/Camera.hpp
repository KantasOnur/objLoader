#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Shader.hpp"
#include <string>
#include <SDL2/SDL.h>

class Camera
{
private:
    glm::vec3 m_Eye = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_At = {0.0f, 0.0f, -1.0f};
    glm::vec3 m_Up = {0.0f, 1.0f, 0.0f};
    
    float m_Fov;
    float m_Aspect;
    float m_Near;
    float m_Far;
    
    glm::mat4 m_View = glm::lookAt(m_Eye, m_At, m_Up);
    glm::mat4 m_Proj;
public:
    
    float m_MoveSpeed = 0.005;
    
    Camera(const float& fov, const float& aspect, const float& near, const float& far)
    : m_Fov(fov), m_Aspect(aspect), m_Near(near), m_Far(far) 
    {
        m_Proj = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
    }
    
    void SetEye(glm::vec3 eye) {m_Eye = eye;}
    void SetAt(glm::vec3 at) {m_Eye = at;}
    void SetUp(glm::vec3 up) {m_Eye = up;}
    
    glm::vec3 GetEye() {return m_Eye;}
    glm::vec3 GetAt() {return m_At;}
    glm::vec3 GetUp() {return m_Up;}
    
    void PlaceCamera(const glm::mat4& model, Shader& shader, const std::string& uniform);
    void MoveEye();
};
