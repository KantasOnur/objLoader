#pragma once

#include <stdio.h>
#include "VertexBuffer.hpp"


struct VertexBufferElement
{
    unsigned int count;
    unsigned int type;
    bool normalized;
};

class VertexArray {
    
private:
    unsigned int m_ID;
public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer &vb, Vertex &vertex) const;
};
