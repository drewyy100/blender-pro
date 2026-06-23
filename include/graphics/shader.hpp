#pragma once
#include <string>
#include <GL/gl.h>
#include <glm/glm.hpp>

namespace bp::graphics {

class Shader {
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();
    bool compile(const std::string& vertexSrc, const std::string& fragmentSrc);
    void use() const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, const glm::vec3& value) const;
    void setUniform(const std::string& name, const glm::mat4& value) const;
    GLuint getProgram() const { return m_programId; }
private:
    GLuint compileShader(GLenum type, const std::string& source);
    GLuint m_programId = 0;
};

}