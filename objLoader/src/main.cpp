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
    
    std::vector<Layout> vertexData = {
        {{-.5f, -.5f}, {1.0, 0.0, 0.0, 1.0}},
        {{.5f, -.5f}, {0.0, 1.0, 0.0, 1.0}},
        {{.5f, .5f}, {0.0, 0.0, 1.0, 1.0}},
        {{-.5f, .5f}, {1.0, 0.0, 0.0, 1.0}}
    };
    Vertex data(vertexData);
    
    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexBuffer vb(data);
    VertexArray va;
    IndexBuffer ib(indices);

    va.AddBuffer(vb, data);
    
    Shader shader("shaders/Basic.vert", "shaders/Basic.frag");
    shader.Bind();
    
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
