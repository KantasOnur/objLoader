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

Subject::Subject(Subject* parent)
: modelPtr_(parent->modelPtr_)
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

   // models_.push(modelMatrix_);
    //for(int i = 0; i < translates_.size(); i++)
    //{
        //std::cout << "a" << std::endl;
      //  modelMatrix_ = glm::translate(modelMatrix_, translates_[i]);
    //}
    //translates_.clear();
    
    modelMatrix_ = *modelPtr_;
    setMV(shader, viewMatrix, projMatrix);

    va_->bind();
    glDrawElements(GL_TRIANGLES, (int)indices_.size(), GL_UNSIGNED_INT, nullptr);
    va_->unbind();
    
    modelMatrix_ = glm::mat4(1.0f);
    //modelMatrix_ = models_.top();
    //models_.pop();
    //shader_.Unbind();
}

void Subject::transform(const glm::mat4& transformedMatrix)
{
    modelMatrix_ = transformedMatrix * (*modelPtr_);
}
