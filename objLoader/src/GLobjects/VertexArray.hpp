#ifndef VertexArray_hpp
#define VertexArray_hpp

#include "Subject.hpp"
#include "VertexBuffer.hpp"

namespace GLobjects {
class VertexArray{
private:
    unsigned int id_;
public:
    VertexArray();
    ~VertexArray();
    void bind() const;
    void unbind() const;
    void addBuffer(const VertexBuffer& vb, const Subject* subject) const;
};
}

#endif /* VertexArray_hpp */

