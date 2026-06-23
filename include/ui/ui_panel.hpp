#pragma once
#include <string>

namespace bp::ui {

class UIPanel {
public:
    virtual ~UIPanel() = default;
    virtual void draw() = 0;
    const std::string& getName() const { return m_name; }
protected:
    explicit UIPanel(const std::string& name) : m_name(name) {}
    std::string m_name;
};

}