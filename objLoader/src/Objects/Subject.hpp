#ifndef Subject_hpp
#define Subject_hpp

#include <vector>
#include <stack>
#include <queue>
#include <glm/gtc/matrix_transform.hpp>
#include "../Shader.hpp"

namespace GLobjects {
    class VertexBuffer;
    class IndexBuffer;
    class VertexArray;
}

struct Layout {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec3 normal;

};

struct SubjectInfo
{
    std::vector<Layout> data;
    std::vector<unsigned int> indices;
};

class Subject {

protected:
    std::vector<Layout> data_;
    std::vector<unsigned int> indices_;
    Shader* shader_;
    
    void updateVertices();
    void bindBuffers();
    
    
private:
    GLobjects::VertexBuffer* vb_;
    GLobjects::VertexArray* va_;
    GLobjects::IndexBuffer* ib_;
    glm::mat4 modelMatrix_ = glm::mat4(1.0f);
    
    void setMV(const glm::mat4& viewMatrix, const glm::mat4& projMatrix);

public:
    
    Subject(Shader* shader, std::vector<Layout> data, std::vector<unsigned int> indices)
    : shader_(shader), data_(data), indices_(indices) {}
    
    Subject(Shader* shader);

    static const unsigned int layoutSize_ = 3;
    const unsigned int counts_[layoutSize_] = {Layout().position.length(), Layout().color.length(), Layout().normal.length()};
    const unsigned int strides_[layoutSize_] = {offsetof(Layout, position), offsetof(Layout, color), offsetof(Layout, normal)};
    
    ~Subject();
    void transform(const glm::mat4& transformationMatrix);
    void makeChildOf(const Subject* subject);
    void draw(const glm::mat4& viewM, const glm::mat4& projectionM);
    void setColor(const glm::vec4& color);
    
    void updateVertex(const glm::vec3 &position, const unsigned int &index);
    glm::vec3 getVertex(const unsigned int &index);
    };

#endif /* Subject_hpp */

