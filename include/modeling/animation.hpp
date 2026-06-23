#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include <map>

namespace bp::modeling {

struct KeyFrame {
    float time = 0.0f;
    glm::vec3 value = {0, 0, 0};
};

class AnimationCurve {
public:
    AnimationCurve(const std::string& name = "Curve");
    void addKeyFrame(const KeyFrame& frame);
    void removeKeyFrame(size_t index);
    const std::vector<KeyFrame>& getKeyFrames() const;
    glm::vec3 evaluate(float time) const;
    float getDuration() const;
private:
    std::string m_name;
    std::vector<KeyFrame> m_keyFrames;
    glm::vec3 interpolate(const KeyFrame& a, const KeyFrame& b, float t) const;
};

class Animation {
public:
    Animation(const std::string& name = "Animation");
    void addCurve(const std::string& property, std::shared_ptr<AnimationCurve> curve);
    std::shared_ptr<AnimationCurve> getCurve(const std::string& property) const;
    void setDuration(float duration);
    float getDuration() const;
    void setFPS(float fps);
    float getFPS() const;
private:
    std::string m_name;
    std::map<std::string, std::shared_ptr<AnimationCurve>> m_curves;
    float m_duration = 0.0f;
    float m_fps = 24.0f;
};

}