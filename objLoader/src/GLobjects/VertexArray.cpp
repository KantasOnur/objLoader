#include "VertexArray.hpp"
#include <GL/glew.h>
#include <iostream>
GLobjects::VertexArray::VertexArray(){
    glGenVertexArrays(1, &id_);
    bind();
}

GLobjects::VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id_);
}

void GLobjects::VertexArray::bind() const {
    glBindVertexArray(id_);
}

void GLobjects::VertexArray::unbind() const {
    glBindVertexArray(0);
}

void GLobjects::VertexArray::addBuffer(const VertexBuffer& vb, const Subject* subject) const {
    vb.bind();
    for (int i = 0; i < 2; i++) {
        const auto& offset = subject->strides_[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, subject->counts_[i], GL_FLOAT, GL_FALSE, sizeof(Layout), (void*)offset);
    }
}

