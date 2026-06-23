#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>
#include <string>

namespace bp::modeling {

class Mesh;

class SceneObject {
public:
    explicit SceneObject(const std::string& name = "Object");
    virtual ~SceneObject() = default;
    const std::string& getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }
    void setPosition(const glm::vec3& position);
    void setRotation(const glm::quat& rotation);
    void setScale(const glm::vec3& scale);
    glm::vec3 getPosition() const { return glm::vec3(m_transform[3]); }
    glm::quat getRotation() const { return m_rotation; }
    glm::vec3 getScale() const { return m_scale; }
    glm::mat4 getTransform() const { return m_transform; }
    void setMesh(std::shared_ptr<Mesh> mesh) { m_mesh = mesh; }
    std::shared_ptr<Mesh> getMesh() const { return m_mesh; }
private:
    std::string m_name;
    glm::mat4 m_transform;
    glm::quat m_rotation = glm::quat(1, 0, 0, 0);
    glm::vec3 m_scale = {1, 1, 1};
    std::shared_ptr<Mesh> m_mesh;
};

class Scene {
public:
    Scene();
    void addObject(std::shared_ptr<SceneObject> object);
    void removeObject(const std::shared_ptr<SceneObject>& object);
    const std::vector<std::shared_ptr<SceneObject>>& getObjects() const;
    void setActiveObject(const std::shared_ptr<SceneObject>& object);
    std::shared_ptr<SceneObject> getActiveObject() const;
    void clear();
private:
    std::shared_ptr<SceneObject> m_rootObject;
    std::vector<std::shared_ptr<SceneObject>> m_objects;
    std::shared_ptr<SceneObject> m_activeObject;
};

}