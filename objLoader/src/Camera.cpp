#include "Camera.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "EventManager.hpp"
#include "Subject.hpp"
#include "ShaderManager.h"

Camera::Camera(GLFWwindow* window, const float& fov, const float& aspect, const float& near, const float& far)
: window_(window), handler_([this] (const MouseClickEvent& event) {onMouseClickEvent(event);})
{
    /*
    std::unique_ptr<EventHandlerWrapper<MouseClickEvent>> handler = std::make_unique<EventHandlerWrapper<MouseClickEvent>>(handler_);
    
    EventManager::getInstance().sub(std::move(handler));
     */
    projectionM_ = glm::perspective(glm::radians(fov), aspect, near, far);
}


void Camera::PlaceCamera(const Shader& shader, const float& dt)
{
    dt_ = dt;
    Inputs();
    viewM_ = glm::lookAt(eye_, eye_ + at_, up_);
    shader.SetUniformVec3f("u_EyePos", eye_);
}

void Camera::Inputs()
{
    glm::vec3 movementVector = {0.0f, 0.0f, 0.0f};
    glm::vec3 leftVector = glm::normalize(glm::cross(up_, at_));
    
    int currentTabState = glfwGetKey(window_, GLFW_KEY_TAB);
    int currentQState = glfwGetKey(window_, GLFW_KEY_Q);
    
    int currentClick = glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT);
    if(!levelEditorMode_)
    {
        if(glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS)
        {
            movementVector += at_;
        }
        if(glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS)
        {
            movementVector -= at_;
        }
        if(glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
        {
            movementVector += leftVector;
        }
        if(glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
        {
            movementVector -= leftVector;
        }
        if(glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            movementVector += up_;
        }
        if(glfwGetKey(window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            movementVector -= up_;
        }
        if (movementVector != glm::vec3(0.0f, 0.0f, 0.0f))
        {
            eye_ += (glm::normalize(movementVector) * movementSpeed_ * dt_);
        }
        
        
        if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            if (!initalClick)
            {
                glfwSetCursorPos(window_, (640 / 2), (480 / 2));
                initalClick = true;
                
                MouseClickEvent event(0, 0, 1);
                EventManager::getInstance().triggerEvent(event);
            }
        }
        
        if(initalClick)
        {
            double xpos;
            double ypos;
            glfwGetCursorPos(window_, &xpos, &ypos);
            
            float deltaX = xpos - 640.0f / 2;
            float deltaY = ypos - 480.0f / 2;
            
            yaw_ += dt_ * mouseSensetivity_ * deltaX;
            pitch_ -= dt_ * mouseSensetivity_ * deltaY;
            
            float maxPitch = 89.0f;
            pitch_ = glm::clamp(pitch_, -maxPitch, maxPitch);
            
            glm::vec3 front;
            front.x = (cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
            front.y = sin(glm::radians(pitch_));
            front.z = (sin(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
            
            at_ = glm::normalize(front);
            glfwSetCursorPos(window_, 640.0f / 2, 480.0f / 2);
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
    }
    
    /*
    if(levelEditorMode_)
    {
        double xpos, ypos;
        glfwGetCursorPos(window_, &xpos, &ypos);
        glm::vec3 worldCoords = pixelToWorld(xpos, ypos, 640, 480, projectionM_, viewM_);
        std::cout << glm::to_string(worldCoords) << std::endl;
        
        
    }
    */
    
    if(levelEditorMode_)
    {
        double xpos, ypos;
        glfwGetCursorPos(window_, &xpos, &ypos);
        LevelEditorEvent event(xpos, ypos);
        
        if(currentClick == GLFW_PRESS && prevClick == GLFW_RELEASE)
        {
            event.firstClick_ = true;
            //std::cout << "im hit" << std::endl;
            EventManager::getInstance().triggerEvent(event);
        }
        if(currentClick == GLFW_PRESS && prevClick == GLFW_PRESS)
        {
            event.firstClick_ = false;
            //std::cout << "im holding" << std::endl;
            EventManager::getInstance().triggerEvent(event);
        }
    }
    
    
    
    if(currentTabState == GLFW_PRESS && currentQState == GLFW_PRESS && (!prevTabState || !prevQState))
    {
        levelEditorMode_ = !levelEditorMode_;
        std::cout << "Level editor mode is: " << levelEditorMode_ << std::endl;
        
        if(levelEditorMode_)
        {
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            eye_.y += 2.0f;
            at_ = glm::vec3(0.0f, -1.0f, 0.0f);
            up_ = glm::vec3(0.0f ,0.0f, -1.0f);

        }
        else
        {
            eye_.y -= 2.0f;
            at_ = {0.0f, 0.0f, -1.0f};
            up_ = glm::vec3(0.0f, 1.0f, 0.0f);
        }
    }
    
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        initalClick = false;
    }
    
    // std::cout << glm::to_string(at_) << std::endl;

    
    prevQState = currentQState;
    prevTabState = currentTabState;
    prevClick = currentClick;
    
}

void Camera::onMouseClickEvent(const MouseClickEvent &event)
{
    std::cout << event.button_ << std::endl;
}


glm::vec3 Camera::pixelToWorld(double x, double y, int width, int height, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    // Step 1: Normalize Device Coordinates
    float ndcX = (2.0f * x) / width - 1.0f;
    float ndcY = 1.0f - (2.0f * y) / height;
    float ndcZ = 1.0f; // Assuming we're dealing with the far plane

    
    // Step 2: Clip Coordinates
    glm::vec4 clipCoords = glm::vec4(ndcX, ndcY, ndcZ, 1.0f);

    // Step 3: View Coordinates
    glm::vec4 viewCoords = glm::inverse(projectionMatrix) * clipCoords;
    viewCoords = glm::vec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);

    // Step 4: World Coordinates
    glm::vec4 worldCoords = glm::inverse(viewMatrix) * viewCoords;
    glm::vec3 worldPosition = glm::vec3(worldCoords);

    return worldPosition;
}
