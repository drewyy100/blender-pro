#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace bp::modeling {

class RigidBody {
public:
    RigidBody();
    void setMass(float mass);
    float getMass() const { return m_mass; }
    void setVelocity(const glm::vec3& vel);
    glm::vec3 getVelocity() const { return m_velocity; }
    void setAcceleration(const glm::vec3& acc);
    glm::vec3 getAcceleration() const { return m_acceleration; }
    void applyForce(const glm::vec3& force);
    void addConstraint(const glm::vec3& constraint);
    void update(float deltaTime);
private:
    float m_mass = 1.0f;
    glm::vec3 m_velocity = {0, 0, 0};
    glm::vec3 m_acceleration = {0, 0, 0};
    glm::vec3 m_force = {0, 0, 0};
    std::vector<glm::vec3> m_constraints;
};

class PhysicsWorld {
public:
    PhysicsWorld();
    void setGravity(const glm::vec3& gravity);
    glm::vec3 getGravity() const { return m_gravity; }
    void addRigidBody(std::shared_ptr<RigidBody> body);
    void removeRigidBody(const std::shared_ptr<RigidBody>& body);
    void simulate(float deltaTime);
private:
    glm::vec3 m_gravity = {0, -9.81f, 0};
    std::vector<std::shared_ptr<RigidBody>> m_bodies;
};

}