#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "Subject.hpp"

class Cube : public Subject
{
private:
    std::vector<Layout> cubeData_ = 
    {
        // Front face
        {{-0.5f, -0.5f, 0.5f}, {1.0, 0.0, 0.0, 1.0}},
        {{0.5f, -0.5f, 0.5f}, {0.0, 1.0, 0.0, 1.0}},
        {{0.5f, 0.5f, 0.5f}, {0.0, 0.0, 1.0, 1.0}},
        {{-0.5f, 0.5f, 0.5f}, {1.0, 0.0, 0.0, 1.0}},

        // Back face
        {{-0.5f, -0.5f, -0.5f}, {1.0, 1.0, 0.0, 1.0}},
        {{0.5f, -0.5f, -0.5f}, {0.0, 1.0, 1.0, 1.0}},
        {{0.5f, 0.5f, -0.5f}, {0.0, 1.0, 0.0, 1.0}},
        {{-0.5f, 0.5f, -0.5f}, {1.0, 1.0, 0.0, 1.0}}
    };
    
    std::vector<unsigned int> cubeIndices_ = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        3, 7, 4,
        4, 0, 3,

        // Right face
        1, 5, 6,
        6, 2, 1,

        // Top face
        3, 2, 6,
        6, 7, 3,

        // Bottom face
        0, 1, 5,
        5, 4, 0
    };
public:
    Cube();
};


#endif /* Cube_hpp */
