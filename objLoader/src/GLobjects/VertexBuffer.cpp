#include "VertexBuffer.hpp"
#include <GL/glew.h>

GLobjects::VertexBuffer::VertexBuffer(const std::vector<Layout>& data) {
    glGenBuffers(1, &id_);
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(Layout) * data.size(), data.data(), GL_STATIC_DRAW);
}

GLobjects::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id_);
}

void GLobjects::VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void GLobjects::VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

