#ifndef ShaderManager_h
#define ShaderManager_h
#include "Shader.hpp"
#include <unordered_map>
#include <string>


struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1); // or use boost::hash_combine
    }
};


class ShaderManager
{
private:
    std::unordered_map<std::pair<std::string, std::string>, Shader, pair_hash> manager;
    ShaderManager() {}
public:
    void addShader(const Shader& shader)
    {
        manager[shader.location_] = shader;
    }
    Shader getShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        return manager[std::make_pair(vertexShader, fragmentShader)];
    }
    static ShaderManager& getInstance()
    {
        static ShaderManager s;
        return s;
    }
};

#endif /* ShaderManager_h */
