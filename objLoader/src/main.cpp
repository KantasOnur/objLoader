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
#include "Cube.hpp"
#include "Octahedron.hpp"
#include "Light.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace glm;

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
    Shader lampShader("shaders/Lamp.vert", "shaders/Lamp.frag");
    
    Cube cube;
    Cube lamp;
    
    //Octahedron octahedron;
    std::vector<unsigned int> rip;
    //octahedron.subdivide(rip, 4);
    //shader.Bind();
    //lampShader.Bind();
    
    float prevTime = 0;
    Camera camera(window, 45.0f, 640.0f/480.0f, 0.1f, 10.0f);
    Light light(vec3(1.0f, 1.0f, 1.0f));
    
    while(!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        float dt = currentTime - prevTime;
        prevTime = currentTime;
        
        camera.PlaceCamera(shader, dt);
                
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        //light.place(shader, );
        //light.place(shader, translate(vec3(1, 0, 0)) * vec4(light.position_, 1.0f));
        /*
        lamp.transform(rotate(currentTime, vec3(0, 1, 0)));
        lamp.transform(translate(vec3(1, 0, 0)));
        lamp.transform(scale(vec3(0.25, 0.25, 0.25)));
        lamp.draw(lampShader, camera.viewM_, camera.projectionM_);
        */
        
        light.transform(rotate(currentTime, vec3(0, 1, 0)));
        light.transform(translate(vec3(1, 0, 0)));
        light.transform(scale(vec3(0.10, 0.10, 0.10)));
        light.illuminate(lampShader, shader, camera);
        
        // Order is T, R, S
        
        
        cube.setColor(vec4(1.0f, 0.5f, 0.5f, 1.0f));
        cube.transform(translate(vec3(0, 0, 0)));
        //cube.transform(rotate(currentTime, vec3(1, 0, 0)));
        cube.transform(scale(vec3(0.5, 0.5, 0.5)));
        cube.draw(shader, camera.viewM_, camera.projectionM_);
         
        /*
        octahedron.transform(translate(vec3(0, 0, -2)));
        octahedron.draw(shader, camera.viewM_, camera.projectionM_);
        */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
