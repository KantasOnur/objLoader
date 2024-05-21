#pragma once

#include <GL/glew.h>
#include <vector>

class IndexBuffer
{
private:
    unsigned int m_ID;
public:
    IndexBuffer(std::vector<unsigned int> &indices);
    ~IndexBuffer();
    
    void Bind() const;
    void Unbind() const;
};
