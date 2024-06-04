#ifndef Octahedron_hpp
#define Octahedron_hpp

#include <stdio.h>
#include "Subject.hpp"
#include <map>

class Octahedron : public Subject
{
public:
    std::vector<Layout> octahedronData_ =
    {
        
        {{0, 1.0, 0}, {1.0, 0.0, 0.0, 1.0}},
        {{-0.5/sqrt(0.5), 0, 0.5/sqrt(0.5)}, {0.0, 1.0, 0.0, 1.0}},
        {{0.5/sqrt(0.5), 0, 0.5/sqrt(0.5)}, {0.0, 0.0, 1.0, 1.0}},
        
        {{0.5/sqrt(0.5), 0, -0.5/sqrt(0.5)}, {1.0, 1.0, 0.0, 1.0}},
        {{-0.5/sqrt(0.5), 0, -0.5/sqrt(0.5)}, {0.5, 1.0, 0.0, 1.0}},
        {{0, -1.0 , 0}, {0.5, 1.0, 0.5, 1.0}}
         
        /*
        {{0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 0.0}},
        {{-1.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}},
        {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}
        */
    };
    
    std::vector<unsigned int> octahedronIndices_
    {
        
        // Top half
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 1, 4,
        
        // Bottom half
        5, 1, 2,
        5, 2, 3,
        5, 3, 4,
        5, 1, 4
        
    };
    
    SubjectInfo info_ = {octahedronData_, octahedronIndices_};
public:
    Octahedron();
    void subdivide(std::vector<unsigned int>& rip, const int& n);
};
#endif /* Octahedron_hpp */
