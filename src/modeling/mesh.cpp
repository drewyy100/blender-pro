#include "modeling/mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

namespace bp::modeling {

Mesh::Mesh() : m_name("Mesh"), m_boundMin(0), m_boundMax(0) {}
Mesh::Mesh(const std::string& name) : m_name(name), m_boundMin(0), m_boundMax(0) {}
Mesh::~Mesh() = default;

void Mesh::addVertex(const Vertex& vertex) { m_vertices.push_back(vertex); }
void Mesh::setVertices(const std::vector<Vertex>& vertices) { m_vertices = vertices; }
const std::vector<Vertex>& Mesh::getVertices() const { return m_vertices; }
void Mesh::setIndices(const std::vector<uint32_t>& indices) { m_indices = indices; }
const std::vector<uint32_t>& Mesh::getIndices() const { return m_indices; }

void Mesh::recalculateNormals() {
    for (auto& vertex : m_vertices) vertex.normal = glm::vec3(0.0f);
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        uint32_t idx0 = m_indices[i], idx1 = m_indices[i + 1], idx2 = m_indices[i + 2];
        glm::vec3 v0 = m_vertices[idx0].position;
        glm::vec3 v1 = m_vertices[idx1].position;
        glm::vec3 v2 = m_vertices[idx2].position;
        glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        m_vertices[idx0].normal += normal;
        m_vertices[idx1].normal += normal;
        m_vertices[idx2].normal += normal;
    }
    for (auto& vertex : m_vertices) vertex.normal = glm::normalize(vertex.normal);
}

void Mesh::recalculateTangents() {
    for (auto& vertex : m_vertices) {
        vertex.tangent = glm::vec3(0.0f);
        vertex.bitangent = glm::vec3(0.0f);
    }
    for (size_t i = 0; i < m_indices.size(); i += 3) {
        uint32_t idx0 = m_indices[i], idx1 = m_indices[i + 1], idx2 = m_indices[i + 2];
        glm::vec3 pos0 = m_vertices[idx0].position;
        glm::vec3 pos1 = m_vertices[idx1].position;
        glm::vec3 pos2 = m_vertices[idx2].position;
        glm::vec2 tex0 = m_vertices[idx0].texCoord;
        glm::vec2 tex1 = m_vertices[idx1].texCoord;
        glm::vec2 tex2 = m_vertices[idx2].texCoord;
        glm::vec3 edge1 = pos1 - pos0;
        glm::vec3 edge2 = pos2 - pos0;
        glm::vec2 deltaUV1 = tex1 - tex0;
        glm::vec2 deltaUV2 = tex2 - tex0;
        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
        glm::vec3 tangent = f * (deltaUV2.y * edge1 - deltaUV1.y * edge2);
        glm::vec3 bitangent = f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2);
        m_vertices[idx0].tangent += tangent;
        m_vertices[idx1].tangent += tangent;
        m_vertices[idx2].tangent += tangent;
        m_vertices[idx0].bitangent += bitangent;
        m_vertices[idx1].bitangent += bitangent;
        m_vertices[idx2].bitangent += bitangent;
    }
    for (auto& vertex : m_vertices) {
        vertex.tangent = glm::normalize(vertex.tangent);
        vertex.bitangent = glm::normalize(vertex.bitangent);
    }
}

void Mesh::recalculateBounds() {
    if (m_vertices.empty()) return;
    m_boundMin = m_vertices[0].position;
    m_boundMax = m_vertices[0].position;
    for (const auto& vertex : m_vertices) {
        m_boundMin = glm::min(m_boundMin, vertex.position);
        m_boundMax = glm::max(m_boundMax, vertex.position);
    }
}

}