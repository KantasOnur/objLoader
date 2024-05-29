#include "IndexBuffer.hpp"
#include <GL/glew.h>

GLobjects::IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices){
    glGenBuffers(1, &id_);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

GLobjects::IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id_);
}

void GLobjects::IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void GLobjects::IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

