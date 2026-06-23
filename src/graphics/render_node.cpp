#include "graphics/render_node.hpp"
#include "core/logger.hpp"
#include <algorithm>

namespace bp::graphics {

ColorNode::ColorNode(const std::string& name) : RenderNode(name, "Color") {}
void ColorNode::evaluate() {}
void ColorNode::setInput(const std::string& name, const std::string& value) {}
std::string ColorNode::getOutput(const std::string& name) const { return ""; }
void ColorNode::setColor(const glm::vec3& color) { m_color = color; }

MixNode::MixNode(const std::string& name) : RenderNode(name, "Mix") {}
void MixNode::evaluate() {}
void MixNode::setInput(const std::string& name, const std::string& value) {}
std::string MixNode::getOutput(const std::string& name) const { return ""; }
void MixNode::setBlendFactor(float factor) { m_factor = glm::clamp(factor, 0.0f, 1.0f); }

VectorMathNode::VectorMathNode(const std::string& name) : RenderNode(name, "VectorMath") {}
void VectorMathNode::evaluate() {}
void VectorMathNode::setInput(const std::string& name, const std::string& value) {}
std::string VectorMathNode::getOutput(const std::string& name) const { return ""; }
void VectorMathNode::setOperation(const std::string& op) { m_operation = op; }

RenderNodeGraph::RenderNodeGraph() {}

void RenderNodeGraph::addNode(std::shared_ptr<RenderNode> node) {
    if (!node) return;
    m_nodes.push_back(node);
    bp::core::Logger::debug("Added render node: {}", node->getName());
}

void RenderNodeGraph::removeNode(const std::string& nodeName) {
    auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
                          [&nodeName](const std::shared_ptr<RenderNode>& n) { return n->getName() == nodeName; });
    if (it != m_nodes.end()) {
        m_nodes.erase(it);
        bp::core::Logger::debug("Removed render node: {}", nodeName);
    }
}

std::shared_ptr<RenderNode> RenderNodeGraph::getNode(const std::string& nodeName) const {
    auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
                          [&nodeName](const std::shared_ptr<RenderNode>& n) { return n->getName() == nodeName; });
    if (it != m_nodes.end()) return *it;
    return nullptr;
}

void RenderNodeGraph::connect(const std::string& srcNode, const std::string& srcOutput, const std::string& dstNode, const std::string& dstInput) {
    auto src = getNode(srcNode);
    auto dst = getNode(dstNode);
    if (!src || !dst) {
        bp::core::Logger::warn("Invalid node connection");
        return;
    }
    m_connections[{dstNode, dstInput}] = {srcNode, srcOutput};
    bp::core::Logger::debug("Connected {} -> {}", srcNode, dstNode);
}

void RenderNodeGraph::evaluate() {
    for (auto& node : m_nodes) {
        if (node) node->evaluate();
    }
}

}