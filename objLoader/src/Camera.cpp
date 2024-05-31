#include "Camera.hpp"
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

Camera::Camera(GLFWwindow* window, const float& fov, const float& aspect, const float& near, const float& far)
: window_(window)
{
    projectionM_ = glm::perspective(glm::radians(fov), aspect, near, far);
}


void Camera::PlaceCamera(const Shader& shader, const float& dt)
{
    dt_ = dt;
    Inputs();
    viewM_ = glm::lookAt(eye_, eye_ + at_, up_);
    glm::mat4 mvp = projectionM_ * viewM_;
    shader.SetUniformMat4f("u_MVP", mvp);
}

void Camera::Inputs()
{
    glm::vec3 movementVector = {0.0f, 0.0f, 0.0f};
    glm::vec3 leftVector = glm::normalize(glm::cross(up_, at_));
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
    
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        initalClick = false;
    }
}

