#pragma once
#include <memory>
#include <cstdint>

namespace bp::modeling {

class Mesh;

class MeshOperations {
public:
    static std::unique_ptr<Mesh> createCube(float size = 1.0f);
    static std::unique_ptr<Mesh> createSphere(float radius = 1.0f, uint32_t subdivisions = 16);
    static std::unique_ptr<Mesh> createPlane(float width = 1.0f, float height = 1.0f, uint32_t widthSegments = 1, uint32_t heightSegments = 1);
    static std::unique_ptr<Mesh> subdivide(const Mesh& mesh);
};

}