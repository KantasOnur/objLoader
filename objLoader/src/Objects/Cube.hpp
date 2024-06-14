#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "Subject.hpp"

class Cube : public Subject
{    
public:
    Cube(const Shader& shader);
    void setShader(const Shader& shader);
};


#endif /* Cube_hpp */
