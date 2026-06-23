#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <map>

namespace bp::graphics {

class RenderNode {
public:
    virtual ~RenderNode() = default;
    virtual void evaluate() = 0;
    virtual void setInput(const std::string& name, const std::string& value) = 0;
    virtual std::string getOutput(const std::string& name) const = 0;
    const std::string& getName() const { return m_name; }
    const std::string& getType() const { return m_type; }

protected:
    RenderNode(const std::string& name, const std::string& type) : m_name(name), m_type(type) {}
    std::string m_name;
    std::string m_type;
};

class ColorNode : public RenderNode {
public:
    ColorNode(const std::string& name = "Color");
    void evaluate() override;
    void setInput(const std::string& name, const std::string& value) override;
    std::string getOutput(const std::string& name) const override;
    void setColor(const glm::vec3& color);
    glm::vec3 getColor() const { return m_color; }

private:
    glm::vec3 m_color = {1.0f, 1.0f, 1.0f};
};

class MixNode : public RenderNode {
public:
    MixNode(const std::string& name = "Mix");
    void evaluate() override;
    void setInput(const std::string& name, const std::string& value) override;
    std::string getOutput(const std::string& name) const override;
    void setBlendFactor(float factor);
    float getBlendFactor() const { return m_factor; }

private:
    float m_factor = 0.5f;
};

class VectorMathNode : public RenderNode {
public:
    VectorMathNode(const std::string& name = "VectorMath");
    void evaluate() override;
    void setInput(const std::string& name, const std::string& value) override;
    std::string getOutput(const std::string& name) const override;
    void setOperation(const std::string& op);
    std::string getOperation() const { return m_operation; }

private:
    std::string m_operation = "add";
};

class RenderNodeGraph {
public:
    RenderNodeGraph();
    void addNode(std::shared_ptr<RenderNode> node);
    void removeNode(const std::string& nodeName);
    std::shared_ptr<RenderNode> getNode(const std::string& nodeName) const;
    void connect(const std::string& srcNode, const std::string& srcOutput, const std::string& dstNode, const std::string& dstInput);
    void evaluate();
    const std::vector<std::shared_ptr<RenderNode>>& getNodes() const { return m_nodes; }

private:
    std::vector<std::shared_ptr<RenderNode>> m_nodes;
    std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string>> m_connections;
};

}