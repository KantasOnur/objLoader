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

class Subject {
protected:
    std::vector<Layout> data_ = {
        {{-0.5f, -0.5f, 0.0f}, {1.0, 0.0, 0.0, 1.0}},
        {{0.5f, -0.5f, 0.0f}, {0.0, 1.0, 0.0, 1.0}},
        {{0.5f, 0.5f, 0.0f}, {0.0, 0.0, 1.0, 1.0}},
        {{-0.5f, 0.5f, 0.0f}, {1.0, 0.0, 0.0, 1.0}}
    };
    std::vector<unsigned int> indices_ = {
        0, 1, 2,
        2, 3, 0
    };
private:
    GLobjects::VertexBuffer* vb_;
    GLobjects::VertexArray* va_;
    GLobjects::IndexBuffer* ib_;
    glm::mat4 modelMatrix_ = glm::mat4(1.0f);
public:
    const unsigned int counts_[2] = {3, 4};
    const unsigned int strides_[2] = {offsetof(Layout, position), offsetof(Layout, color)};
public:
    Subject();
    ~Subject();
    
    void transform(const glm::mat4& transformationMatrix);
    void makeChildOf(const Subject* subject);
    void draw(const Shader& shader, const glm::mat4& viewM, const glm::mat4& projectionM);
    
private:
    void setMV(const Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix);
};

#endif /* Subject_hpp */

