#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace bp::core {

class MathUtils {
public:
    static glm::mat4 createTransformMatrix(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
    static void decomposeMatrix(const glm::mat4& matrix, glm::vec3& position, glm::quat& rotation, glm::vec3& scale);
    static glm::vec3 closestPointOnTriangle(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
    static bool rayTriangleIntersection(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t, glm::vec3& barycentric);
    static glm::vec3 smoothstep(const glm::vec3& edge0, const glm::vec3& edge1, const glm::vec3& x);
};

}