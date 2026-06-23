#pragma once
#include <memory>
#include <string>
#include <vector>

namespace bp::modeling {
class Scene;
class SceneObject;
class Mesh;
}

namespace bp::editor {

class SceneManager {
public:
    SceneManager();
    ~SceneManager();
    void newScene();
    void saveScene(const std::string& filepath);
    void loadScene(const std::string& filepath);
    std::shared_ptr<bp::modeling::Scene> getActiveScene() const;
private:
    std::shared_ptr<bp::modeling::Scene> m_activeScene;
    std::string m_lastFilepath;
};

}