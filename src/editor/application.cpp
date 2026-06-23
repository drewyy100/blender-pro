#include "editor/application.hpp"
#include "editor/scene_manager.hpp"
#include "graphics/renderer.hpp"
#include "graphics/camera.hpp"
#include "ui/ui_manager.hpp"
#include "modeling/scene.hpp"
#include "modeling/mesh_operations.hpp"
#include "core/logger.hpp"
#include <GLFW/glfw3.h>

namespace bp::editor {

Application::Application() 
    : m_renderer(std::make_unique<bp::graphics::Renderer>()),
      m_uiManager(std::make_unique<bp::ui::UIManager>()),
      m_scene(std::make_unique<bp::modeling::Scene>()),
      m_running(false),
      m_windowTitle("Blender Pro v0.1.0") {}

Application::~Application() = default;

bool Application::initialize() {
    bp::core::Logger::info("Initializing Application");
    if (!m_renderer->initialize()) {
        bp::core::Logger::error("Failed to initialize renderer");
        return false;
    }
    if (!m_uiManager->initialize()) {
        bp::core::Logger::error("Failed to initialize UI");
        return false;
    }
    auto cube = bp::modeling::MeshOperations::createCube(2.0f);
    auto sceneObj = std::make_shared<bp::modeling::SceneObject>("Cube");
    m_scene->addObject(sceneObj);
    m_scene->setActiveObject(sceneObj);
    bp::core::Logger::info("Application initialized successfully");
    m_running = true;
    return true;
}

void Application::run() {
    bp::core::Logger::info("Starting application loop");
    while (m_running) {
        m_renderer->beginFrame();
        m_uiManager->beginFrame();
        m_uiManager->update();
        m_renderer->endFrame();
        m_uiManager->endFrame();
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            m_running = false;
        }
    }
}

void Application::shutdown() {
    bp::core::Logger::info("Shutting down application");
    m_uiManager->shutdown();
    m_renderer->shutdown();
}

}