#include "modeling/scene.hpp"
#include "modeling/mesh.hpp"
#include <algorithm>

namespace bp::modeling {

SceneObject::SceneObject(const std::string& name) : m_name(name), m_transform(1.0f) {}

void SceneObject::setPosition(const glm::vec3& position) {
    m_transform[3] = glm::vec4(position, 1.0f);
}

void SceneObject::setRotation(const glm::quat& rotation) {
    m_rotation = rotation;
}

void SceneObject::setScale(const glm::vec3& scale) {
    m_scale = scale;
}

Scene::Scene() : m_rootObject(std::make_shared<SceneObject>("Root")) {}

void Scene::addObject(std::shared_ptr<SceneObject> object) {
    m_objects.push_back(object);
}

void Scene::removeObject(const std::shared_ptr<SceneObject>& object) {
    auto it = std::find(m_objects.begin(), m_objects.end(), object);
    if (it != m_objects.end()) {
        m_objects.erase(it);
    }
}

const std::vector<std::shared_ptr<SceneObject>>& Scene::getObjects() const {
    return m_objects;
}

void Scene::setActiveObject(const std::shared_ptr<SceneObject>& object) {
    m_activeObject = object;
}

std::shared_ptr<SceneObject> Scene::getActiveObject() const {
    return m_activeObject;
}

void Scene::clear() {
    m_objects.clear();
    m_activeObject = nullptr;
}

}