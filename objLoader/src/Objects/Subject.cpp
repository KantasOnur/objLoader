#define GLM_ENABLE_EXPERIMENTAL
#include "Subject.hpp"
#include <GL/glew.h>
#include <iostream>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "glm/gtx/string_cast.hpp"

Subject::Subject(const Shader& shader)
: shader_(shader)
{
    bindBuffers();
}

void Subject::bindBuffers()
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
    std::cout << "im free" << std::endl;
    delete va_;
    delete vb_;
    delete ib_;
    va_ = nullptr;
    vb_ = nullptr;
    ib_ = nullptr;
}

void Subject::setMV(const Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
    shader.SetUniformMat4f("u_ModelMatrix", modelMatrix_);
    shader.SetUniformMat4f("u_ViewMatrix", viewMatrix);
    shader.SetUniformMat4f("u_ProjectionMatrix", projMatrix);
}

void Subject::draw(const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
    
    shader_.Bind();
    
    setMV(shader_, viewMatrix, projMatrix);

    va_->bind();
    glDrawElements(GL_TRIANGLES, (int)indices_.size(), GL_UNSIGNED_INT, nullptr);
    va_->unbind();
    
    modelMatrix_ = glm::mat4(1.0f);
}

void Subject::setColor(const glm::vec4& color)
{
    for(auto& vertex : data_)
    {
        vertex.color = color;
    }
    updateVertices();
}

void Subject::transform(const glm::mat4 &transformationMatrix)
{
    modelMatrix_ = modelMatrix_ * transformationMatrix;
}
void Subject::makeChildOf(const Subject *subject)
{
    modelMatrix_ = subject->modelMatrix_;
}

void Subject::updateVertices()
{
    /*
    for(int i = 0; i < data_.size(); i++)
    {
        std::cout << glm::to_string(data_.data()[i].position) << std::endl;
    }
    
    for(int i = 0; i < indices_.size(); i++)
    {
        std::cout << indices_[i] << std::endl;
    }
    */
    
    vb_->bind();
    ib_->bind();

    glBufferData(GL_ARRAY_BUFFER, data_.size() * sizeof(Layout), data_.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);
    
    vb_->unbind();
    ib_->unbind();
     

}
