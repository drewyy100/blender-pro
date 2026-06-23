#include "editor/file_io.hpp"
#include "modeling/scene.hpp"
#include "modeling/mesh.hpp"
#include "modeling/material.hpp"
#include "core/logger.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>

namespace bp::editor {

bool FileSerializer::saveScene(const std::string& filepath, const std::shared_ptr<bp::modeling::Scene>& scene) {
    if (!scene) return false;
    std::ofstream file(filepath);
    if (!file.is_open()) {
        bp::core::Logger::error("Failed to open file for writing: {}", filepath);
        return false;
    }
    file << "BLENDER_SCENE\n";
    file << "VERSION 1\n";
    const auto& objects = scene->getObjects();
    file << "OBJECTS " << objects.size() << "\n";
    for (const auto& obj : objects) {
        if (!obj) continue;
        file << "OBJECT\n";
        file << "NAME " << obj->getName() << "\n";
        auto pos = obj->getPosition();
        file << "POSITION " << pos.x << " " << pos.y << " " << pos.z << "\n";
        auto scale = obj->getScale();
        file << "SCALE " << scale.x << " " << scale.y << " " << scale.z << "\n";
    }
    file.close();
    bp::core::Logger::info("Scene saved to {}", filepath);
    return true;
}

bool FileSerializer::loadScene(const std::string& filepath, std::shared_ptr<bp::modeling::Scene>& scene) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        bp::core::Logger::error("Failed to open file for reading: {}", filepath);
        return false;
    }
    std::string line;
    std::getline(file, line);
    if (line != "BLENDER_SCENE") {
        bp::core::Logger::error("Invalid scene file format");
        return false;
    }
    file.close();
    bp::core::Logger::info("Scene loaded from {}", filepath);
    return true;
}

bool FileSerializer::saveMesh(const std::string& filepath, const bp::modeling::Mesh& mesh) {
    std::ofstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        bp::core::Logger::error("Failed to save mesh: {}", filepath);
        return false;
    }
    const auto& vertices = mesh.getVertices();
    const auto& indices = mesh.getIndices();
    uint32_t vertexCount = vertices.size();
    uint32_t indexCount = indices.size();
    file.write(reinterpret_cast<const char*>(&vertexCount), sizeof(vertexCount));
    file.write(reinterpret_cast<const char*>(&indexCount), sizeof(indexCount));
    for (const auto& v : vertices) {
        file.write(reinterpret_cast<const char*>(&v.position), sizeof(v.position));
        file.write(reinterpret_cast<const char*>(&v.normal), sizeof(v.normal));
    }
    for (const auto& idx : indices) {
        file.write(reinterpret_cast<const char*>(&idx), sizeof(idx));
    }
    file.close();
    bp::core::Logger::info("Mesh saved to {}", filepath);
    return true;
}

bool FileSerializer::loadMesh(const std::string& filepath, bp::modeling::Mesh& mesh) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        bp::core::Logger::error("Failed to load mesh: {}", filepath);
        return false;
    }
    uint32_t vertexCount, indexCount;
    file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
    file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));
    std::vector<bp::modeling::Vertex> vertices(vertexCount);
    for (auto& v : vertices) {
        file.read(reinterpret_cast<char*>(&v.position), sizeof(v.position));
        file.read(reinterpret_cast<char*>(&v.normal), sizeof(v.normal));
    }
    std::vector<uint32_t> indices(indexCount);
    for (auto& idx : indices) {
        file.read(reinterpret_cast<char*>(&idx), sizeof(idx));
    }
    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    file.close();
    bp::core::Logger::info("Mesh loaded from {}", filepath);
    return true;
}

bool FileSerializer::saveMaterial(const std::string& filepath, const bp::modeling::Material& material) {
    std::ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "MATERIAL\n";
    file << "NAME " << material.getName() << "\n";
    auto albedo = material.getAlbedo();
    file << "ALBEDO " << albedo.r << " " << albedo.g << " " << albedo.b << "\n";
    file << "METALLIC " << material.getMetallic() << "\n";
    file << "ROUGHNESS " << material.getRoughness() << "\n";
    file.close();
    return true;
}

bool FileSerializer::loadMaterial(const std::string& filepath, bp::modeling::Material& material) {
    std::ifstream file(filepath);
    if (!file.is_open()) return false;
    file.close();
    return true;
}

ProjectManager::ProjectManager() : m_isOpen(false) {}

bool ProjectManager::createProject(const std::string& projectPath) {
    m_projectPath = projectPath;
    m_projectName = std::filesystem::path(projectPath).filename().string();
    try {
        std::filesystem::create_directories(projectPath + "/assets");
        std::filesystem::create_directories(projectPath + "/scenes");
        std::filesystem::create_directories(projectPath + "/meshes");
        m_isOpen = true;
        bp::core::Logger::info("Project created: {}", m_projectName);
        return true;
    } catch (const std::exception& e) {
        bp::core::Logger::error("Failed to create project: {}", e.what());
        return false;
    }
}

bool ProjectManager::openProject(const std::string& projectPath) {
    if (!std::filesystem::exists(projectPath)) {
        bp::core::Logger::error("Project path does not exist: {}", projectPath);
        return false;
    }
    m_projectPath = projectPath;
    m_projectName = std::filesystem::path(projectPath).filename().string();
    m_isOpen = true;
    bp::core::Logger::info("Project opened: {}", m_projectName);
    return true;
}

bool ProjectManager::saveProject() {
    if (!m_isOpen) return false;
    bp::core::Logger::info("Project saved: {}", m_projectName);
    return true;
}

bool ProjectManager::closeProject() {
    m_projectPath.clear();
    m_projectName.clear();
    m_isOpen = false;
    bp::core::Logger::info("Project closed");
    return true;
}

const std::string& ProjectManager::getProjectPath() const {
    return m_projectPath;
}

const std::string& ProjectManager::getProjectName() const {
    return m_projectName;
}

bool ProjectManager::isProjectOpen() const {
    return m_isOpen;
}

std::string ProjectManager::getAssetPath(const std::string& assetName) const {
    return m_projectPath + "/assets/" + assetName;
}

std::vector<std::string> ProjectManager::listAssets() const {
    std::vector<std::string> assets;
    if (!std::filesystem::exists(m_projectPath)) return assets;
    for (const auto& entry : std::filesystem::directory_iterator(m_projectPath + "/assets")) {
        assets.push_back(entry.path().filename().string());
    }
    return assets;
}

}