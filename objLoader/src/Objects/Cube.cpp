#include "Cube.hpp"

Cube::Cube()
{
    data_ = cubeData_;
    indices_ = cubeIndices_;
    bindBuffers();
}
