#include "Octahedron.hpp"
#include <unordered_map>

struct KeyFuncs
{
    
    size_t operator()(const glm::vec3& k)const
    {
        return std::hash<float>()(k.x) ^ std::hash<float>()(k.y) ^ std::hash<float>()(k.z);
    }
    bool operator()(const glm::vec3& a, const glm::vec3& b)const
        {
                return a.x == b.x && a.y == b.y && a.z == b.z;
        }
};

typedef std::unordered_map<glm::vec3, unsigned int, KeyFuncs, KeyFuncs> map;

Octahedron::Octahedron()
{
    data_ = octahedronData_;
    indices_ = octahedronIndices_;
    bindBuffers();
}

void Octahedron::subdivide(std::vector<unsigned int>& rip, const int& n)
{
    if(n == 0)
    {
        updateVertices();
    }
    else
    {
        map map;
        unsigned int indicesSize = indices_.size();
        unsigned int dataSize = data_.size();
        rip.clear();
        for(int i = 0; i < indicesSize; i += 3)
        {
            std::vector<glm::vec3> triangle =
            {
                data_[indices_[i]].position,
                data_[indices_[i + 1]].position,
                data_[indices_[i + 2]].position
            };
            
            std::vector<glm::vec3> midTriangle =
            {
                (triangle[0] + triangle[1]) * 0.5f,
                (triangle[0] + triangle[2]) * 0.5f,
                (triangle[1] + triangle[2]) * 0.5f
            };
            
            
            for(int j = 0; j < midTriangle.size(); j++)
            {
                if (map.insert(std::pair(midTriangle[j], dataSize)).second != false)
                {
                    data_.push_back({glm::normalize(midTriangle[j]), glm::vec4(1.0f)});
                    dataSize++;
                }
            }
            
            rip.push_back(indices_[i + 1]);
            rip.push_back(map[midTriangle[0]]);
            rip.push_back(map[midTriangle[2]]);
            
            rip.push_back(indices_[i]);
            rip.push_back(map[midTriangle[0]]);
            rip.push_back(map[midTriangle[1]]);
            
            rip.push_back(map[midTriangle[0]]);
            rip.push_back(map[midTriangle[1]]);
            rip.push_back(map[midTriangle[2]]);
            
            rip.push_back(map[midTriangle[2]]);
            rip.push_back(map[midTriangle[1]]);
            rip.push_back(indices_[i + 2]);
            
        }
        indices_ = rip;
        subdivide(rip, n - 1);
    }
}
