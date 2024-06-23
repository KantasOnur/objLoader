#ifndef ShaderManager_h
#define ShaderManager_h
#include "Shader.hpp"
#include <unordered_map>
#include <string>

#define GET_SHADER(shader) \
    ShaderManager::getInstance().getShader("shaders/" #shader ".vert", "shaders/" #shader ".frag")

#define ADD_SHADER(shader) \
    ShaderManager::getInstance().addShader(std::make_unique<Shader>("shaders/" #shader ".vert", "shaders/" #shader ".frag"));

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
    std::unordered_map<std::pair<std::string, std::string>, std::unique_ptr<Shader>, pair_hash> manager;
    ShaderManager() {}
public:
    void addShader(std::unique_ptr<Shader>&& shaderPtr)
    {
        manager[shaderPtr->location_] = std::move(shaderPtr);
    }
    Shader* getShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        return manager[std::make_pair(vertexShader, fragmentShader)].get();
    }
    static ShaderManager& getInstance()
    {
        static ShaderManager s;
        return s;
    }
};

#endif /* ShaderManager_h */
