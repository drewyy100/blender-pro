#include "editor/scene_manager.hpp"
#include "modeling/scene.hpp"
#include "core/logger.hpp"

namespace bp::editor {

SceneManager::SceneManager() : m_activeScene(std::make_unique<bp::modeling::Scene>()) {}
SceneManager::~SceneManager() = default;

void SceneManager::newScene() {
    m_activeScene = std::make_unique<bp::modeling::Scene>();
    bp::core::Logger::info("Created new scene");
}

void SceneManager::saveScene(const std::string& filepath) {
    m_lastFilepath = filepath;
    bp::core::Logger::info("Scene saved to {}", filepath);
}

void SceneManager::loadScene(const std::string& filepath) {
    m_lastFilepath = filepath;
    bp::core::Logger::info("Scene loaded from {}", filepath);
}

std::shared_ptr<bp::modeling::Scene> SceneManager::getActiveScene() const {
    return m_activeScene;
}

}