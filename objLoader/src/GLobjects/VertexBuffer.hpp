#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include "Subject.hpp"

namespace GLobjects {
class VertexBuffer{
private:
    unsigned int id_;
public:
    VertexBuffer(const std::vector<Layout>& data);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
};
}

#endif /* VertexBuffer_hpp */

