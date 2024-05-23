#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

float eyeZ = 0;
float eyeX = 0;
void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    std::cout << key << std::endl;
    switch (key) {
        case 87:
            eyeZ -= 0.1;
            break;
            
        case 83:
            eyeZ += 0.1;
            break;
            
        case 68:
            eyeX += 0.1;
            break;
        case 65:
            eyeX -= 0.1;
            break;
    }
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
      std::cout << "I'm apple machine" << std::endl;
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, keyCallBack);
    
    glfwMakeContextCurrent(window);
    
    if(glewInit() != GLEW_OK)
    {
        std::cout << "failed" << std::endl;
    }
    
    std::vector<Layout> vertexData = {
        {{-0.5f, -0.5f}, {1.0, 0.0, 0.0, 1.0}},
        {{0.5f, -0.5f}, {0.0, 1.0, 0.0, 1.0}},
        {{0.5f, 0.5f}, {0.0, 0.0, 1.0, 1.0}},
        {{-0.5f, 0.5f}, {1.0, 0.0, 0.0, 1.0}}
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
    
    //glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 1.0f, -1.0f);
    
   
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 proj = glm::perspective(glm::radians(100.0f), 960.0f/540.0f, 0.01f, 1000.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(eyeX, 0, eyeZ), glm::vec3(eyeX, 0, eyeZ - 1.0), glm::vec3(0, 1, 0));
        
        shader.SetUniformMat4f("u_ProjectionMatrix", proj);
        shader.SetUniformMat4f("u_ViewMatrix", view);
        
        glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
