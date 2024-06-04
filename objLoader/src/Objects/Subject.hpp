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
    void updateVertices();
private:
    GLobjects::VertexBuffer* vb_;
    GLobjects::VertexArray* va_;
    GLobjects::IndexBuffer* ib_;
    glm::mat4 modelMatrix_ = glm::mat4(1.0f);
    
    void setMV(const Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix);

public:
    const unsigned int counts_[2] = {Layout().position.length(), Layout().color.length()};
    const unsigned int strides_[2] = {offsetof(Layout, position), offsetof(Layout, color)};

    ~Subject();
    void bindBuffers();
    void transform(const glm::mat4& transformationMatrix);
    void makeChildOf(const Subject* subject);
    void draw(const Shader& shader, const glm::mat4& viewM, const glm::mat4& projectionM);
    };

#endif /* Subject_hpp */

