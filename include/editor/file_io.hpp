#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace bp::modeling {
class Scene;
class Mesh;
class Material;
}

namespace bp::editor {

class FileSerializer {
public:
    static bool saveScene(const std::string& filepath, const std::shared_ptr<bp::modeling::Scene>& scene);
    static bool loadScene(const std::string& filepath, std::shared_ptr<bp::modeling::Scene>& scene);
    static bool saveMesh(const std::string& filepath, const bp::modeling::Mesh& mesh);
    static bool loadMesh(const std::string& filepath, bp::modeling::Mesh& mesh);
    static bool saveMaterial(const std::string& filepath, const bp::modeling::Material& material);
    static bool loadMaterial(const std::string& filepath, bp::modeling::Material& material);
};

class ProjectManager {
public:
    ProjectManager();
    bool createProject(const std::string& projectPath);
    bool openProject(const std::string& projectPath);
    bool saveProject();
    bool closeProject();
    const std::string& getProjectPath() const;
    const std::string& getProjectName() const;
    bool isProjectOpen() const;
    std::string getAssetPath(const std::string& assetName) const;
    std::vector<std::string> listAssets() const;

private:
    std::string m_projectPath;
    std::string m_projectName;
    bool m_isOpen;
};

}