#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


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
    
public:
    Shader(const std::string& vertLocation, const std::string& fragLocation);
    ~Shader();
    
    void Bind() const;
    void Unbind() const;
    
    ShaderProgramSource ReadShader(std::string& vertLocation, std::string& fragLocation);
    int CreateShader(const std::string& vert, const std::string& frag);
    unsigned int CompileShader(const std::string& source, unsigned int type);
};
