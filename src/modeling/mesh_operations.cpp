#include "modeling/mesh_operations.hpp"
#include "modeling/mesh.hpp"
#include <glm/glm.hpp>
#include <algorithm>
#include <map>

namespace bp::modeling {

std::unique_ptr<Mesh> MeshOperations::createCube(float size) {
    auto mesh = std::make_unique<Mesh>("Cube");
    float s = size * 0.5f;
    std::vector<Vertex> vertices = {
        {{-s, -s, -s}, {0, 0, -1}, {0, 0}, {1, 0, 0}, {0, 1, 0}},
        {{s, -s, -s}, {0, 0, -1}, {1, 0}, {1, 0, 0}, {0, 1, 0}},
        {{s, s, -s}, {0, 0, -1}, {1, 1}, {1, 0, 0}, {0, 1, 0}},
        {{-s, s, -s}, {0, 0, -1}, {0, 1}, {1, 0, 0}, {0, 1, 0}},
        {{-s, -s, s}, {0, 0, 1}, {1, 0}, {1, 0, 0}, {0, 1, 0}},
        {{s, -s, s}, {0, 0, 1}, {0, 0}, {1, 0, 0}, {0, 1, 0}},
        {{s, s, s}, {0, 0, 1}, {0, 1}, {1, 0, 0}, {0, 1, 0}},
        {{-s, s, s}, {0, 0, 1}, {1, 1}, {1, 0, 0}, {0, 1, 0}},
    };
    std::vector<uint32_t> indices = {
        0, 1, 2, 0, 2, 3, 4, 6, 5, 4, 7, 6, 0, 4, 5, 0, 5, 1, 2, 6, 7, 2, 7, 3, 0, 3, 7, 0, 7, 4, 1, 5, 6, 1, 6, 2,
    };
    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    mesh->recalculateNormals();
    mesh->recalculateBounds();
    return mesh;
}

std::unique_ptr<Mesh> MeshOperations::createSphere(float radius, uint32_t subdivisions) {
    auto mesh = std::make_unique<Mesh>("Sphere");
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t latSteps = subdivisions;
    uint32_t lonSteps = subdivisions * 2;
    for (uint32_t lat = 0; lat <= latSteps; ++lat) {
        float theta = (float)lat / latSteps * glm::pi<float>();
        float sinTheta = glm::sin(theta);
        float cosTheta = glm::cos(theta);
        for (uint32_t lon = 0; lon <= lonSteps; ++lon) {
            float phi = (float)lon / lonSteps * 2.0f * glm::pi<float>();
            float sinPhi = glm::sin(phi);
            float cosPhi = glm::cos(phi);
            glm::vec3 pos = radius * glm::vec3(sinTheta * cosPhi, cosTheta, sinTheta * sinPhi);
            glm::vec3 normal = glm::normalize(pos);
            glm::vec2 texCoord((float)lon / lonSteps, (float)lat / latSteps);
            vertices.push_back({pos, normal, texCoord, {1, 0, 0}, {0, 1, 0}});
        }
    }
    for (uint32_t lat = 0; lat < latSteps; ++lat) {
        for (uint32_t lon = 0; lon < lonSteps; ++lon) {
            uint32_t a = lat * (lonSteps + 1) + lon;
            uint32_t b = a + lonSteps + 1;
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(a + 1);
            indices.push_back(a + 1);
            indices.push_back(b);
            indices.push_back(b + 1);
        }
    }
    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    mesh->recalculateNormals();
    mesh->recalculateBounds();
    return mesh;
}

std::unique_ptr<Mesh> MeshOperations::createPlane(float width, float height, uint32_t widthSegments, uint32_t heightSegments) {
    auto mesh = std::make_unique<Mesh>("Plane");
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;
    for (uint32_t y = 0; y <= heightSegments; ++y) {
        for (uint32_t x = 0; x <= widthSegments; ++x) {
            float px = -halfWidth + (float)x / widthSegments * width;
            float py = -halfHeight + (float)y / heightSegments * height;
            glm::vec2 texCoord((float)x / widthSegments, (float)y / heightSegments);
            vertices.push_back({{{px, 0.0f, py}}, {0, 1, 0}, texCoord, {1, 0, 0}, {0, 0, 1}});
        }
    }
    for (uint32_t y = 0; y < heightSegments; ++y) {
        for (uint32_t x = 0; x < widthSegments; ++x) {
            uint32_t a = y * (widthSegments + 1) + x;
            uint32_t b = a + widthSegments + 1;
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(a + 1);
            indices.push_back(a + 1);
            indices.push_back(b);
            indices.push_back(b + 1);
        }
    }
    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    mesh->recalculateBounds();
    return mesh;
}

std::unique_ptr<Mesh> MeshOperations::subdivide(const Mesh& mesh) {
    auto subdivided = std::make_unique<Mesh>(mesh.getName() + "_subdivided");
    std::vector<Vertex> newVertices = mesh.getVertices();
    std::vector<uint32_t> newIndices;
    std::map<uint64_t, uint32_t> edgeMap;
    const auto& indices = mesh.getIndices();
    for (size_t i = 0; i < indices.size(); i += 3) {
        uint32_t idx0 = indices[i], idx1 = indices[i + 1], idx2 = indices[i + 2];
        auto getEdgeIndex = [&](uint32_t a, uint32_t b) {
            if (a > b) std::swap(a, b);
            uint64_t edge = ((uint64_t)a << 32) | b;
            if (edgeMap.find(edge) == edgeMap.end()) {
                uint32_t idx = newVertices.size();
                Vertex v;
                v.position = (newVertices[a].position + newVertices[b].position) * 0.5f;
                v.normal = glm::normalize((newVertices[a].normal + newVertices[b].normal) * 0.5f);
                v.texCoord = (newVertices[a].texCoord + newVertices[b].texCoord) * 0.5f;
                newVertices.push_back(v);
                edgeMap[edge] = idx;
            }
            return edgeMap[edge];
        };
        uint32_t e01 = getEdgeIndex(idx0, idx1);
        uint32_t e12 = getEdgeIndex(idx1, idx2);
        uint32_t e20 = getEdgeIndex(idx2, idx0);
        newIndices.push_back(idx0);
        newIndices.push_back(e01);
        newIndices.push_back(e20);
        newIndices.push_back(e01);
        newIndices.push_back(idx1);
        newIndices.push_back(e12);
        newIndices.push_back(e20);
        newIndices.push_back(e12);
        newIndices.push_back(idx2);
        newIndices.push_back(e01);
        newIndices.push_back(e12);
        newIndices.push_back(e20);
    }
    subdivided->setVertices(newVertices);
    subdivided->setIndices(newIndices);
    subdivided->recalculateNormals();
    subdivided->recalculateBounds();
    return subdivided;
}

}