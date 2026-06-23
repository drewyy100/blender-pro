#include "core/math_utils.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

namespace bp::core {

glm::mat4 MathUtils::createTransformMatrix(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) {
    glm::mat4 mat = glm::mat4_cast(rotation);
    mat[0] *= scale.x;
    mat[1] *= scale.y;
    mat[2] *= scale.z;
    mat[3] = glm::vec4(position, 1.0f);
    return mat;
}

void MathUtils::decomposeMatrix(const glm::mat4& matrix, glm::vec3& position, glm::quat& rotation, glm::vec3& scale) {
    position = glm::vec3(matrix[3]);
    glm::vec3 col0(matrix[0]);
    glm::vec3 col1(matrix[1]);
    glm::vec3 col2(matrix[2]);
    scale.x = glm::length(col0);
    scale.y = glm::length(col1);
    scale.z = glm::length(col2);
    glm::mat3 rotMatrix(col0 / scale.x, col1 / scale.y, col2 / scale.z);
    rotation = glm::quat_cast(rotMatrix);
}

glm::vec3 MathUtils::closestPointOnTriangle(const glm::vec3& p, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 ap = p - a;
    float d1 = glm::dot(ab, ap);
    float d2 = glm::dot(ac, ap);
    if (d1 <= 0.0f && d2 <= 0.0f) return a;
    glm::vec3 bp = p - b;
    float d3 = glm::dot(ab, bp);
    float d4 = glm::dot(ac, bp);
    if (d3 >= 0.0f && d4 <= d3) return b;
    glm::vec3 cp = p - c;
    float d5 = glm::dot(ab, cp);
    float d6 = glm::dot(ac, cp);
    if (d6 >= 0.0f && d5 <= d6) return c;
    float vc = d1 * d4 - d3 * d2;
    if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
        float v = d1 / (d1 - d3);
        return a + v * ab;
    }
    float vb = d5 * d2 - d1 * d6;
    if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
        float v = d2 / (d2 - d6);
        return a + v * ac;
    }
    float va = d3 * d6 - d5 * d4;
    float denom = 1.0f / (va + vb + vc);
    float v = vb * denom;
    float w = vc * denom;
    return a + ab * v + ac * w;
}

bool MathUtils::rayTriangleIntersection(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t, glm::vec3& barycentric) {
    const float EPSILON = 1e-8f;
    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    glm::vec3 h = glm::cross(rayDir, edge2);
    float a = glm::dot(edge1, h);
    if (std::abs(a) < EPSILON) return false;
    float f = 1.0f / a;
    glm::vec3 s = rayOrigin - v0;
    float u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f) return false;
    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(rayDir, q);
    if (v < 0.0f || u + v > 1.0f) return false;
    t = f * glm::dot(edge2, q);
    if (t > EPSILON) {
        barycentric = glm::vec3(1.0f - u - v, u, v);
        return true;
    }
    return false;
}

glm::vec3 MathUtils::smoothstep(const glm::vec3& edge0, const glm::vec3& edge1, const glm::vec3& x) {
    glm::vec3 t = glm::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

}