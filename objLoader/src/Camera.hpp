#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Shader.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>

static void lookAround(GLFWwindow* window, float xpos, float ypos);

class Camera
{
private:
    glm::vec3 eye_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 at_ = {0.0f, 0.0f, -1.0f};
    glm::vec3 up_ = {0.0f, 1.0f, 0.0f};
    
    float movementSpeed_ = 2.5f;
    float yaw_ = glm::degrees(atan2(at_.z, at_.x));
    float pitch_ = atan2(at_.y, sqrt(at_.x * at_.x + at_.z * at_.z));
    float mouseSensetivity_ = 10.0f;
    GLFWwindow* window_;
    float dt_;
    
    bool initalClick = false;
public:
    glm::mat4 viewM_;
    glm::mat4 projectionM_;
    
    Camera(GLFWwindow* window, const float& fov, const float& aspect, const float& near, const float& far);
    
    void PlaceCamera(const Shader& shader, const float& dt);
    glm::vec3 getCameraPos() {return eye_;}
private:
    void Inputs();
    //void MoveEye();
    //void EyeLookAround(float& yaw, float& pitch) {m_Yaw += yaw; m_Pitch += pitch;}
    //void mouse_callback(GLFWwindow *window, float xpos, float ypos);
};
