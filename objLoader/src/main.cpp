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


glm::mat4 LookAt(glm::vec3 eye, glm::vec3 at, glm::vec3 up)
{
    glm::vec3 v = glm::normalize(at - eye);
    glm::vec3 n = glm::normalize(glm::cross(v, up));
    glm::vec3 u = glm::normalize(glm::cross(n, v));
    v = -v;
    
    glm::mat4 result(glm::vec4(n, -glm::dot(n, eye)),
                     glm::vec4(u, -glm::dot(u, eye)),
                     glm::vec4(v, -glm::dot(v, eye)),
                     glm::vec4(0.0f, 0.0f, 0.0f, 1.0));
    return result;
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
    
    glfwMakeContextCurrent(window);
    
    if(glewInit() != GLEW_OK)
    {
        std::cout << "failed" << std::endl;
    }
    
    std::vector<Layout> vertexData = {
        {{100.0f, 100.0f}, {1.0, 0.0, 0.0, 1.0}},
        {{200.0f, 100.0f}, {0.0, 1.0, 0.0, 1.0}},
        {{200.0f, 200.0f}, {0.0, 0.0, 1.0, 1.0}},
        {{100.0f, 200.0f}, {1.0, 0.0, 0.0, 1.0}}
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
    
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 1.0f, -1.0f);
    shader.SetUniformMat4f("u_ProjectionMatrix", proj);
    //glm::vec3 eye(0, 0, 0);
    
    
    
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
