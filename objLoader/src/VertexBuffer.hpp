#pragma once

#include "VertexLayout.h"
#include <GL/glew.h>


class VertexBuffer
{
private:
    unsigned int m_ID;
public:
    VertexBuffer(Vertex &data);
    ~VertexBuffer();
    
    void Bind() const;
    void Unbind() const;
};
