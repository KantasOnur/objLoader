#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "glm/gtc/matrix_transform.hpp"
#include <string>

struct ShaderProgramSource
{
    std::string vertexShader;
    std::string fragmentShader;
};

class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_VertLocation;
    std::string m_FragLocation;
    ShaderProgramSource shaderSource_;
public:
    
    std::pair<std::string, std::string> location_;
    Shader(const std::string& vertLocation, const std::string& fragLocation);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
    
    void SetUniformMat4f(const std::string& variable, const glm::mat4& matrix) const;
    void SetUniformVec3f(const std::string& variable, const glm::vec3& vector) const;
    
    ShaderProgramSource ReadShader(std::string& vertLocation, std::string& fragLocation);
    int CreateShader(const std::string& vert, const std::string& frag);
    unsigned int CompileShader(const std::string& source, unsigned int type);
    int GetLocation(const std::string& variable) const;
    
    std::string toString();
    
    Shader() = default;

};
