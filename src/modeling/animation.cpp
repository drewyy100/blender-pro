#include "modeling/animation.hpp"
#include <algorithm>
#include <cmath>
#include <map>

namespace bp::modeling {

AnimationCurve::AnimationCurve(const std::string& name) : m_name(name) {}

void AnimationCurve::addKeyFrame(const KeyFrame& frame) {
    m_keyFrames.push_back(frame);
    std::sort(m_keyFrames.begin(), m_keyFrames.end(),
              [](const KeyFrame& a, const KeyFrame& b) { return a.time < b.time; });
}

void AnimationCurve::removeKeyFrame(size_t index) {
    if (index < m_keyFrames.size()) {
        m_keyFrames.erase(m_keyFrames.begin() + index);
    }
}

const std::vector<KeyFrame>& AnimationCurve::getKeyFrames() const {
    return m_keyFrames;
}

glm::vec3 AnimationCurve::evaluate(float time) const {
    if (m_keyFrames.empty()) return {0, 0, 0};
    if (time <= m_keyFrames[0].time) return m_keyFrames[0].value;
    if (time >= m_keyFrames.back().time) return m_keyFrames.back().value;
    for (size_t i = 0; i < m_keyFrames.size() - 1; ++i) {
        if (time >= m_keyFrames[i].time && time <= m_keyFrames[i + 1].time) {
            float t = (time - m_keyFrames[i].time) / (m_keyFrames[i + 1].time - m_keyFrames[i].time);
            return interpolate(m_keyFrames[i], m_keyFrames[i + 1], t);
        }
    }
    return m_keyFrames.back().value;
}

float AnimationCurve::getDuration() const {
    if (m_keyFrames.empty()) return 0.0f;
    return m_keyFrames.back().time;
}

glm::vec3 AnimationCurve::interpolate(const KeyFrame& a, const KeyFrame& b, float t) const {
    float smoothT = t * t * (3.0f - 2.0f * t);
    return glm::mix(a.value, b.value, smoothT);
}

Animation::Animation(const std::string& name) : m_name(name) {}

void Animation::addCurve(const std::string& property, std::shared_ptr<AnimationCurve> curve) {
    m_curves[property] = curve;
}

std::shared_ptr<AnimationCurve> Animation::getCurve(const std::string& property) const {
    auto it = m_curves.find(property);
    if (it != m_curves.end()) return it->second;
    return nullptr;
}

void Animation::setDuration(float duration) {
    m_duration = duration;
}

float Animation::getDuration() const {
    return m_duration;
}

void Animation::setFPS(float fps) {
    m_fps = fps;
}

float Animation::getFPS() const {
    return m_fps;
}

}