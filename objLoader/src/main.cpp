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
#include "Camera.hpp"
#include "Subject.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"


int main(void)
{
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
    
    glfwMakeContextCurrent(window);
    
    if(glewInit() != GLEW_OK)
    {
        std::cout << "failed" << std::endl;
    }
    
    Shader shader("shaders/Basic.vert", "shaders/Basic.frag");
    Subject* square = new Subject();
    Subject* square2 = new Subject();
    shader.Bind();
    
    float prevTime = 0;
    Camera camera(window, 45.0f, 640.0f/480.0f, 0.1f, 10.0f);

    while(!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        float dt = currentTime - prevTime;
        prevTime = currentTime;
        camera.PlaceCamera(shader, dt);
        
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        
        
        // Order is T, R, S
        square->transform(glm::translate(glm::vec3(0, 0, -2)));
        square->transform(glm::scale(glm::vec3(0.5, 0.5, 0.5)));
        {
            square2->makeChildOf(square);
            square2->transform(glm::rotate(currentTime, glm::vec3(0, 1, 0)));
            square2->draw(shader, camera.viewM_, camera.projectionM_);
        }
        square->draw(shader, camera.viewM_, camera.projectionM_);
       
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    delete square;
    square = nullptr;
    delete square2;
    square2 = nullptr;
    glfwTerminate();
    return 0;
}
