#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace bp::modeling {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

class Mesh {
public:
    Mesh();
    explicit Mesh(const std::string& name);
    ~Mesh();
    void addVertex(const Vertex& vertex);
    void setVertices(const std::vector<Vertex>& vertices);
    const std::vector<Vertex>& getVertices() const;
    void setIndices(const std::vector<uint32_t>& indices);
    const std::vector<uint32_t>& getIndices() const;
    void recalculateNormals();
    void recalculateTangents();
    void recalculateBounds();
    const glm::vec3& getBoundMin() const { return m_boundMin; }
    const glm::vec3& getBoundMax() const { return m_boundMax; }
    const std::string& getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }
private:
    std::string m_name;
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
    glm::vec3 m_boundMin, m_boundMax;
};

}