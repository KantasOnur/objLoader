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
    float position[3];
    float color[4];
};

class Subject {
protected:
    std::vector<Layout> data_ = {
        {{-0.5f, -0.5f, -2.0f}, {1.0, 0.0, 0.0, 1.0}},
        {{0.5f, -0.5f, -2.0f}, {0.0, 1.0, 0.0, 1.0}},
        {{0.5f, 0.5f, -2.0f}, {0.0, 0.0, 1.0, 1.0}},
        {{-0.5f, 0.5f, -2.0f}, {1.0, 0.0, 0.0, 1.0}}
    };
    std::vector<unsigned int> indices_ = {
        0, 1, 2,
        2, 3, 0
    };
private:
    GLobjects::VertexBuffer* vb_;
    GLobjects::VertexArray* va_;
    GLobjects::IndexBuffer* ib_;
    Shader shader_;
    
    std::stack<glm::mat4> models_;
    std::vector<glm::vec3> translates_;
    
public:
    const unsigned int counts_[2] = {3, 4};
    const unsigned int strides_[2] = {offsetof(Layout, position), offsetof(Layout, color)};
    Subject* nextHiearchy;
    glm::mat4 modelMatrix_ = glm::mat4(1.0f);
public:
    Subject(const Shader& shader);
    Subject(const Shader& shader, const glm::mat4& modelMatrix); // for the heirchy matrix
    ~Subject();
    virtual void draw(const glm::mat4& viewMatrix, const glm::mat4& projMatrix);
    void push_transform();
    void pop_transform();
    void translate(const glm::vec3& position);
private:
    void setMV(const glm::mat4& viewMatrix, const glm::mat4& projMatrix);
};

#endif /* Subject_hpp */

