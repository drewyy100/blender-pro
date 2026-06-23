#include "modeling/physics.hpp"
#include <algorithm>

namespace bp::modeling {

RigidBody::RigidBody() = default;
void RigidBody::setMass(float mass) { m_mass = glm::max(mass, 0.001f); }
void RigidBody::setVelocity(const glm::vec3& vel) { m_velocity = vel; }
void RigidBody::setAcceleration(const glm::vec3& acc) { m_acceleration = acc; }
void RigidBody::applyForce(const glm::vec3& force) { m_force += force; }
void RigidBody::addConstraint(const glm::vec3& constraint) { m_constraints.push_back(constraint); }
void RigidBody::update(float deltaTime) {
    m_acceleration = m_force / m_mass;
    m_velocity += m_acceleration * deltaTime;
    m_force = {0, 0, 0};
}

PhysicsWorld::PhysicsWorld() = default;
void PhysicsWorld::setGravity(const glm::vec3& gravity) { m_gravity = gravity; }
void PhysicsWorld::addRigidBody(std::shared_ptr<RigidBody> body) { m_bodies.push_back(body); }
void PhysicsWorld::removeRigidBody(const std::shared_ptr<RigidBody>& body) {
    auto it = std::find(m_bodies.begin(), m_bodies.end(), body);
    if (it != m_bodies.end()) m_bodies.erase(it);
}
void PhysicsWorld::simulate(float deltaTime) {
    for (auto& body : m_bodies) {
        if (body) {
            body->applyForce(m_gravity * body->getMass());
            body->update(deltaTime);
        }
    }
}

}