#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace bp::graphics {

class Camera {
public:
    Camera(const glm::vec3& position = {0, 0, 5}, const glm::vec3& target = {0, 0, 0}, const glm::vec3& up = {0, 1, 0});
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewProjectionMatrix() const;
    void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);
    void orbitAround(float angleX, float angleY, float distance);
    void pan(const glm::vec3& offset);
    void zoom(float factor);
    void setFOV(float fov);
    void setAspectRatio(float aspect);
    glm::vec3 getForwardVector() const;
    glm::vec3 getRightVector() const;
    glm::vec3 getUpVector() const;
private:
    void updateViewMatrix();
    void updateProjectionMatrix();
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_up;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projMatrix;
    float m_fov;
    float m_aspect;
    float m_near, m_far;
};

}