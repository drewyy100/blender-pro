#include "graphics/renderer.hpp"
#include "core/logger.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace bp::graphics {

struct Renderer::Implementation {
    GLFWwindow* window = nullptr;
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::mat4(1.0f);
    GLuint VAO = 0, VBO = 0, EBO = 0;
    bool initialized = false;
};

Renderer::Renderer() : m_impl(std::make_unique<Implementation>()) {}
Renderer::~Renderer() { shutdown(); }

bool Renderer::initialize() {
    bp::core::Logger::info("Initializing Renderer...");
    if (!glfwInit()) {
        bp::core::Logger::error("Failed to initialize GLFW");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_impl->window = glfwCreateWindow(1920, 1080, "Blender Pro", nullptr, nullptr);
    if (!m_impl->window) {
        bp::core::Logger::error("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_impl->window);
    glfwSwapInterval(1);
    glGenVertexArrays(1, &m_impl->VAO);
    glGenBuffers(1, &m_impl->VBO);
    glGenBuffers(1, &m_impl->EBO);
    m_impl->initialized = true;
    bp::core::Logger::info("Renderer initialized successfully");
    return true;
}

void Renderer::shutdown() {
    if (m_impl->initialized) {
        glDeleteBuffers(1, &m_impl->EBO);
        glDeleteBuffers(1, &m_impl->VBO);
        glDeleteVertexArrays(1, &m_impl->VAO);
        if (m_impl->window) {
            glfwDestroyWindow(m_impl->window);
            glfwTerminate();
        }
        m_impl->initialized = false;
    }
}

void Renderer::beginFrame() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::endFrame() {
    if (m_impl->window) {
        glfwSwapBuffers(m_impl->window);
        glfwPollEvents();
    }
}

void Renderer::renderMesh(const Mesh& mesh, const Material& material, const glm::mat4& transform) {
    glBindVertexArray(m_impl->VAO);
    glDrawElements(GL_TRIANGLES, mesh.getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::setViewMatrix(const glm::mat4& view) {
    m_impl->viewMatrix = view;
}

void Renderer::setProjectionMatrix(const glm::mat4& projection) {
    m_impl->projMatrix = projection;
}

}