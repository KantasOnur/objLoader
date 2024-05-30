#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Shader.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>

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
    
    float m_MoveSpeed = 0.02f;
    float m_Yaw = glm::degrees(atan2(m_At.z, m_At.x));
    float m_Pitch = atan2(m_At.y, sqrt(m_At.x * m_At.x + m_At.z * m_At.z));
    float m_MouseSpeed = 0.1;
    
public:
    glm::mat4 m_View = glm::lookAt(m_Eye, m_At, m_Up);
    glm::mat4 m_Proj;
    
    Camera(const float& fov, const float& aspect, const float& near, const float& far)
    : m_Fov(fov), m_Aspect(aspect), m_Near(near), m_Far(far) 
    {
        m_Proj = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
    }
    
    void SetEye(glm::vec3 eye) {m_Eye = eye;}
    void SetAt(glm::vec3 at) {m_At = at;}
    void SetUp(glm::vec3 up) {m_Up = up;}
    
    glm::vec3 GetEye() {return m_Eye;}
    glm::vec3 GetAt() {return m_At;}
    glm::vec3 GetUp() {return m_Up;}
    
    void PlaceCamera(const glm::mat4& model, Shader& shader, const std::string& uniform);
    void MoveEye();
    void EyeLookAround(float& yaw, float& pitch) {m_Yaw += yaw; m_Pitch += pitch;}
    void mouse_callback(GLFWwindow *window, float xpos, float ypos);
};
