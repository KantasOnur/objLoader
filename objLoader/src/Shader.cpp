#include "Shader.hpp"

Shader::Shader(const std::string& vertLocation, const std::string& fragLocation)
    : m_VertLocation(vertLocation), m_FragLocation(fragLocation)
{
    ShaderProgramSource shaderSource = ReadShader(m_VertLocation, m_FragLocation);
    m_RendererID = CreateShader(shaderSource.vertexShader, shaderSource.fragmentShader);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ReadShader(std::string& vertLocation, std::string& fragLocation)
{
    std::ifstream file(vertLocation);
        
    std::string line;
    std::stringstream ss[2];
    
    for (std::stringstream& source : ss)
    {
        while(std::getline(file, line))
        {
            source << line << '\n';
        }
        file.close();
        file.open(fragLocation);
    }
    file.close();
    return {ss[0].str(), ss[1].str()};
}

int Shader::CreateShader(const std::string& vert, const std::string& frag)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vert, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(frag, GL_FRAGMENT_SHADER);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}
