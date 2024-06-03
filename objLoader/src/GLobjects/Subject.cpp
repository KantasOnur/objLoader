#include "Subject.hpp"
#include <GL/glew.h>
#include <iostream>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"

Subject::Subject()
{
    
    
    va_ = new GLobjects::VertexArray();
    vb_ = new GLobjects::VertexBuffer(data_);
    ib_ = new GLobjects::IndexBuffer(indices_);
    va_->addBuffer(*vb_, this);

    va_->unbind();
    vb_->unbind();
    ib_->unbind();
}

Subject::~Subject()
{
    delete va_;
    delete vb_;
    delete ib_;
    va_ = nullptr;
    vb_ = nullptr;
    ib_ = nullptr;
}

void Subject::setMV(const Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
    glm::mat4 mvp = projMatrix * viewMatrix * modelMatrix_;
    shader.SetUniformMat4f("u_MVP", mvp);
}

void Subject::draw(const Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
    setMV(shader, viewMatrix, projMatrix);

    va_->bind();
    glDrawElements(GL_TRIANGLES, (int)indices_.size(), GL_UNSIGNED_INT, nullptr);
    va_->unbind();
    
    modelMatrix_ = glm::mat4(1.0f);
}

void Subject::transform(const glm::mat4 &transformationMatrix)
{
    modelMatrix_ = modelMatrix_ * transformationMatrix;
}
void Subject::makeChildOf(const Subject *subject)
{
    modelMatrix_ = subject->modelMatrix_;
}
