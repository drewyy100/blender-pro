#include "ui/ui_manager.hpp"
#include "core/logger.hpp"
#include <algorithm>

namespace bp::ui {

UIManager::UIManager() : m_isVisible(true) {}

bool UIManager::initialize() {
    bp::core::Logger::info("Initializing UI Manager");
    return true;
}

void UIManager::shutdown() {
    bp::core::Logger::info("Shutting down UI Manager");
}

void UIManager::beginFrame() {
}

void UIManager::endFrame() {
}

void UIManager::addPanel(const std::shared_ptr<UIPanel>& panel) {
    m_panels.push_back(panel);
}

void UIManager::removePanel(const std::shared_ptr<UIPanel>& panel) {
    auto it = std::find(m_panels.begin(), m_panels.end(), panel);
    if (it != m_panels.end()) {
        m_panels.erase(it);
    }
}

void UIManager::update() {
    for (auto& panel : m_panels) {
        if (panel) {
            panel->draw();
        }
    }
}

void UIManager::setVisible(bool visible) {
    m_isVisible = visible;
}

bool UIManager::isVisible() const {
    return m_isVisible;
}

}