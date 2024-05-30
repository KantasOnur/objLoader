#include "Subject.hpp"
#include <GL/glew.h>
#include <iostream>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"

Subject::Subject(const Shader& shader)
    : shader_(shader)
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

void Subject::setMV(const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
    glm::mat4 mvp = projMatrix * viewMatrix * modelMatrix_;
    shader_.SetUniformMat4f("u_MVP", mvp);
}

void Subject::draw(const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{

    models_.push(modelMatrix_);
    for(int i = 0; i < translates_.size(); i++)
    {
        //std::cout << "a" << std::endl;
        modelMatrix_ = glm::translate(modelMatrix_, translates_[i]);
    }
    translates_.clear();
    
    setMV(viewMatrix, projMatrix);

    va_->bind();
    glDrawElements(GL_TRIANGLES, (int)indices_.size(), GL_UNSIGNED_INT, nullptr);
    va_->unbind();
    
    modelMatrix_ = models_.top();
    models_.pop();
    //shader_.Unbind();
}

void Subject::translate(const glm::vec3& position)
{
    translates_.push_back(position);
}
