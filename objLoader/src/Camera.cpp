#include "Camera.hpp"

void Camera::PlaceCamera(const glm::mat4& model, Shader& shader, const std::string& uniform)
{
    MoveEye();
    //std::cout << glm::to_string(m_At) << std::endl;
    m_View = glm::lookAt(m_Eye, m_Eye + m_At, m_Up);
    //glm::mat4 modelview = m_View * model;
    //glm::mat4 mvp = m_Proj * modelview;
    //shader.SetUniformMat4f("u_MVP", mvp);
}

void Camera::MoveEye()
{
    
    //SDL_Event event;
    glm::vec3 movementVector = {0.0f, 0.0f, 0.0f};
    const Uint8* state = SDL_GetKeyboardState(NULL);
    glm::vec3 leftVector = glm::normalize(glm::cross(m_Up, m_At));
    if(state[SDL_SCANCODE_W])
    {
        movementVector += m_At;
    }
    
    if(state[SDL_SCANCODE_S])
    {
        movementVector -= m_At;
    }
    if(state[SDL_SCANCODE_D])
    {
        movementVector -= leftVector;
    }
    if(state[SDL_SCANCODE_A])
    {
        movementVector += leftVector;
    }
    if(state[SDL_SCANCODE_SPACE])
    {
        movementVector += m_Up;
    }
    if(state[SDL_SCANCODE_LSHIFT])
    {
        movementVector -= m_Up;
    }
    
    if(movementVector != glm::vec3(0.0f, 0.0f, 0.0f))
    {
        m_Eye += (glm::normalize(movementVector) * m_MoveSpeed);
    }
    
}

