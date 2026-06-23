#include "graphics/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace bp::graphics {

Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
    : m_position(position), m_target(target), m_up(glm::normalize(up)), m_fov(45.0f), m_aspect(16.0f / 9.0f), m_near(0.1f), m_far(1000.0f) {
    updateViewMatrix();
    updateProjectionMatrix();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}

void Camera::setPosition(const glm::vec3& position) {
    m_position = position;
    updateViewMatrix();
}

void Camera::setTarget(const glm::vec3& target) {
    m_target = target;
    updateViewMatrix();
}

void Camera::orbitAround(float angleX, float angleY, float distance) {
    glm::vec3 direction = m_position - m_target;
    glm::vec3 right = glm::normalize(glm::cross(direction, m_up));
    glm::vec3 up = glm::normalize(glm::cross(right, direction));
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angleX, up);
    rotation = glm::rotate(rotation, angleY, right);
    glm::vec3 newDir = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    newDir = glm::normalize(newDir) * distance;
    m_position = m_target + newDir;
    updateViewMatrix();
}

void Camera::pan(const glm::vec3& offset) {
    m_position += offset;
    m_target += offset;
    updateViewMatrix();
}

void Camera::zoom(float factor) {
    glm::vec3 direction = m_target - m_position;
    m_position += direction * factor;
    updateViewMatrix();
}

void Camera::setFOV(float fov) {
    m_fov = fov;
    updateProjectionMatrix();
}

void Camera::setAspectRatio(float aspect) {
    m_aspect = aspect;
    updateProjectionMatrix();
}

void Camera::updateViewMatrix() {
    m_viewMatrix = getViewMatrix();
}

void Camera::updateProjectionMatrix() {
    m_projMatrix = getProjectionMatrix();
}

glm::vec3 Camera::getForwardVector() const {
    return glm::normalize(m_target - m_position);
}

glm::vec3 Camera::getRightVector() const {
    return glm::normalize(glm::cross(getForwardVector(), m_up));
}

glm::vec3 Camera::getUpVector() const {
    return m_up;
}

}