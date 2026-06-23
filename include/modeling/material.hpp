#pragma once
#include <glm/glm.hpp>
#include <string>

namespace bp::modeling {

class Material {
public:
    Material(const std::string& name = "Material");
    const std::string& getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }
    void setAlbedo(const glm::vec3& albedo) { m_albedo = albedo; }
    const glm::vec3& getAlbedo() const { return m_albedo; }
    void setMetallic(float metallic) { m_metallic = glm::clamp(metallic, 0.0f, 1.0f); }
    float getMetallic() const { return m_metallic; }
    void setRoughness(float roughness) { m_roughness = glm::clamp(roughness, 0.0f, 1.0f); }
    float getRoughness() const { return m_roughness; }
    void setEmissive(const glm::vec3& emissive) { m_emissive = emissive; }
    const glm::vec3& getEmissive() const { return m_emissive; }
    void setIOR(float ior) { m_ior = glm::clamp(ior, 1.0f, 3.0f); }
    float getIOR() const { return m_ior; }
private:
    std::string m_name;
    glm::vec3 m_albedo = {0.8f, 0.8f, 0.8f};
    float m_metallic = 0.0f;
    float m_roughness = 0.5f;
    glm::vec3 m_emissive = {0.0f, 0.0f, 0.0f};
    float m_ior = 1.5f;
};

}