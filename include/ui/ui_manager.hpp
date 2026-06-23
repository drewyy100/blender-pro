#pragma once
#include "ui/ui_panel.hpp"
#include <memory>
#include <vector>
#include <algorithm>

namespace bp::ui {

class UIManager {
public:
    UIManager();
    bool initialize();
    void shutdown();
    void beginFrame();
    void endFrame();
    void update();
    void addPanel(const std::shared_ptr<UIPanel>& panel);
    void removePanel(const std::shared_ptr<UIPanel>& panel);
    void setVisible(bool visible);
    bool isVisible() const;
private:
    std::vector<std::shared_ptr<UIPanel>> m_panels;
    bool m_isVisible;
};

}