#include "graphics/shader.hpp"
#include "core/logger.hpp"
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace bp::graphics {

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
    compile(vertexSrc, fragmentSrc);
}

Shader::~Shader() {
    if (m_programId != 0) {
        glDeleteProgram(m_programId);
    }
}

bool Shader::compile(const std::string& vertexSrc, const std::string& fragmentSrc) {
    GLuint vertexId = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragmentId = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);
    if (vertexId == 0 || fragmentId == 0) return false;
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexId);
    glAttachShader(m_programId, fragmentId);
    glLinkProgram(m_programId);
    GLint success;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_programId, 512, nullptr, infoLog);
        bp::core::Logger::error("Shader program linking failed: {}", infoLog);
        glDeleteProgram(m_programId);
        m_programId = 0;
        return false;
    }
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    return true;
}

GLuint Shader::compileShader(GLenum type, const std::string& source) {
    GLuint shaderId = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);
    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        bp::core::Logger::error("Shader compilation failed: {}", infoLog);
        glDeleteShader(shaderId);
        return 0;
    }
    return shaderId;
}

void Shader::use() const {
    glUseProgram(m_programId);
}

void Shader::setUniform(const std::string& name, float value) const {
    GLint loc = glGetUniformLocation(m_programId, name.c_str());
    glUniform1f(loc, value);
}

void Shader::setUniform(const std::string& name, int value) const {
    GLint loc = glGetUniformLocation(m_programId, name.c_str());
    glUniform1i(loc, value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const {
    GLint loc = glGetUniformLocation(m_programId, name.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) const {
    GLint loc = glGetUniformLocation(m_programId, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

}