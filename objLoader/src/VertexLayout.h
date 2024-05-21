#pragma once
#include <vector>

struct Layout
{
    float position[2];
    float color[4];
};

class Vertex
{
    
private:
    std::vector<Layout> m_Vector;
public:
    const unsigned char positionIndex = 0;
    const unsigned char colorIndex = 1;
    Vertex(std::vector<Layout> &data) {m_Vector = data;}
    std::vector<Layout> getVector() const {return m_Vector;}
    const Layout* data() const {return m_Vector.data();}
    const unsigned long size() const {return m_Vector.size();}
    const unsigned long m_sizeof() const {return sizeof(Layout) * size();}  
    
    // This is terrible :( maybe there is a better way.
    const unsigned int m_Strides[2] = {
        offsetof(Layout, position),
        offsetof(Layout, color)
    };
    
    const unsigned int m_Counts[2] = {2, 4};
    const unsigned int m_Elements = 2;
    
};
