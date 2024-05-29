#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

#include "Subject.hpp"

namespace GLobjects {
class IndexBuffer{
private:
    unsigned int id_;
public:
    IndexBuffer(const std::vector<unsigned int>& indices);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
};
}

#endif /* IndexBuffer_hpp */

