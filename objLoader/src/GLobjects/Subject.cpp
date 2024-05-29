#include "Subject.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include <GL/glew.h>
#include <iostream>

Subject::Subject() {}

void Subject::draw() {
    GLobjects::VertexBuffer vb(data_);
    GLobjects::VertexArray va;
    va.addBuffer(vb, this);
    GLobjects::IndexBuffer ib(indices_);

    glDrawElements(GL_TRIANGLES, (int)indices_.size(), GL_UNSIGNED_INT, nullptr);
}

