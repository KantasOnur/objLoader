#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, Vertex &vertex) const
{
    vb.Bind();
    for(int i = 0; i < 2; i++)
    {
        const auto &offset = vertex.m_Strides[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, vertex.m_Counts[i], GL_FLOAT, GL_FALSE, sizeof(Layout), (void *) offset);

    }
}
