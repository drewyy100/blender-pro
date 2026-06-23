#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace bp::graphics {

class Mesh;
class Camera;
class Material;

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool initialize();
    void shutdown();
    
    void beginFrame();
    void endFrame();
    
    void renderMesh(const Mesh& mesh, const Material& material, const glm::mat4& transform);
    void setViewMatrix(const glm::mat4& view);
    void setProjectionMatrix(const glm::mat4& projection);
    
private:
    struct Implementation;
    std::unique_ptr<Implementation> m_impl;
};

}
