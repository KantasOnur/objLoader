#define GLM_ENABLE_EXPERIMENTAL
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>

#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexLayout.h"
#include "Camera.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

glm::vec2 prevMousePos = {0.0f, 0.0f};
float mouseSensetivity = 0.1f;

Camera camera(100.0f, 640.0f/480.0f, 0.1f, 10.0f);
glm::vec3 front = {0, 0, -1};

float yaw = glm::degrees(atan2(front.z, front.x));
float pitch = glm::degrees(atan2(front.y, sqrt(front.x * front.x + front.z * front.z)));
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    
    
    float deltaX = xpos - 640.0f / 2;
    float deltaY = ypos - 480.0f / 2;


    float sensitivity = 0.1f;
    yaw += sensitivity * deltaX;
    pitch -= sensitivity * deltaY;

    float maxPitch = 89.0f;
    pitch = glm::clamp(pitch, -maxPitch, maxPitch);

    front.x = (cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    front.y = sin(glm::radians(pitch));
    front.z = (sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

    front = glm::normalize(front);

    camera.SetAt(front);

    glfwSetCursorPos(window, 640.0f / 2, 480.0f / 2);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    
}

int main(void)
{
    std::cout << yaw << std::endl << pitch << std::endl;

    GLFWwindow* window;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 )
    {
        std::cout << "Can't load sdl" << std::endl;
        return -1;
    }
    
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
      std::cout << "I'm apple machine" << std::endl;
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwMakeContextCurrent(window);
    
    if(glewInit() != GLEW_OK)
    {
        std::cout << "failed" << std::endl;
    }
    
    std::vector<Layout> vertexData = {
        {{-0.5f, -0.5f, -2.0f}, {1.0, 0.0, 0.0, 1.0}},
        {{0.5f, -0.5f, -2.0f}, {0.0, 1.0, 0.0, 1.0}},
        {{0.5f, 0.5f, -2.0f}, {0.0, 0.0, 1.0, 1.0}},
        {{-0.5f, 0.5f, -2.0f}, {1.0, 0.0, 0.0, 1.0}}
    };
    Vertex data(vertexData);
    
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexBuffer vb(data);
    VertexArray va;
    va.AddBuffer(vb, data);

    IndexBuffer ib(indices);
    
    Shader shader("shaders/Basic.vert", "shaders/Basic.frag");
    shader.Bind();
    
    Camera camera(100.0f, 640.0f/480.0f, 0.1f, 10.0f);
    
    while (!glfwWindowShouldClose(window))
    {
        camera.PlaceCamera(glm::mat4(1.0f), shader, "u_MVP");

        glClear(GL_COLOR_BUFFER_BIT);
        
        //std::cout << glm::to_string(camera.GetEye()) << std::endl;
        glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
