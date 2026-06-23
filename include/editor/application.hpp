#pragma once

#include <memory>
#include <string>

namespace bp::graphics {
class Renderer;
class Viewport;
}

namespace bp::ui {
class UIManager;
}

namespace bp::modeling {
class Scene;
}

namespace bp::editor {

class Application {
public:
    Application();
    ~Application();
    
    bool initialize();
    void run();
    void shutdown();
    
private:
    std::unique_ptr<bp::graphics::Renderer> m_renderer;
    std::unique_ptr<bp::ui::UIManager> m_uiManager;
    std::unique_ptr<bp::modeling::Scene> m_scene;
    
    bool m_running;
    std::string m_windowTitle;
};

}
