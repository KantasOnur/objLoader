#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>
#include "glm/gtc/matrix_transform.hpp"

struct Layout
{
    float position[3];
    float color[4];
};

class Subject
{
protected:
    std::vector<Layout> data_ =
    {
        {{-0.5f, -0.5f, -2.0f}, {1.0, 0.0, 0.0, 1.0}},
        {{0.5f, -0.5f, -2.0f}, {0.0, 1.0, 0.0, 1.0}},
        {{0.5f, 0.5f, -2.0f}, {0.0, 0.0, 1.0, 1.0}},
        {{-0.5f, 0.5f, -2.0f}, {1.0, 0.0, 0.0, 1.0}}
    };
    std::vector<unsigned int> indices_ =
    {
      0, 1, 2,
      2, 3, 0
    };
    glm::mat4 modelMatrix_;
    
    const unsigned int counts_[2] = {3, 4};
    const unsigned int strides_[2] = {offsetof(Layout, position), offsetof(Layout, color)};
public:
    Subject();
    void draw();
    void push_transform();
    void pop_transform();
private:
    void setMV();
};

#endif // SUBJECT_HPP
